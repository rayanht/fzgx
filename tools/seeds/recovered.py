#!/usr/bin/env python3
"""Freeze every unfinished function with saved C scoring strictly above a threshold."""
from __future__ import annotations

import argparse
import hashlib
import gzip
import json
import os
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from fzgx import oracle
from fzgx.ledger import Ledger
from fzgx.project import ROOT, STATE_DIR, Project


def digest(body):
    return hashlib.sha256(body.encode()).hexdigest()


def percent(record):
    # These measures have different denominators. A binding-adjusted row score
    # must not silently replace objdiff's raw similarity in saved seed ranking.
    for key in ('raw_percent','percent','percent_adjusted','adjusted','best','score'):
        value=record.get(key)
        if isinstance(value,(int,float)):
            return value
    return 0


class LazyRecord(dict):
    """A saved candidate whose C is read from its file on first use: collecting every saved
    body read 180,000 files and 700 MB of reports on each engine start."""

    def __getitem__(self, key):
        if key == 'body' and dict.get(self, 'body') is None and dict.get(self, 'original_path'):
            dict.__setitem__(self, 'body', Path(dict.get(self, 'original_path')).read_text())
        return dict.__getitem__(self, key)

    def get(self, key, default=None):
        if key == 'body':
            try:
                return self['body']
            except OSError:
                return default
        return dict.get(self, key, default)


CACHE_PICKLE = STATE_DIR / 'saved_candidates.pickle'
SHA_CACHE = STATE_DIR / 'saved_candidates_sha.json'


def _fingerprint(threshold, rows):
    """Cheap freshness key over every store collect() reads: file mtimes and sizes of the
    indexes, reports and stores, directory mtimes for the check archives and attempts."""
    parts = [repr(threshold), repr(sorted(rows))]
    def stat(path):
        try:
            s = os.stat(path)
            return f'{path}:{s.st_mtime_ns}:{s.st_size}'
        except OSError:
            return f'{path}:-'
    checks = STATE_DIR / 'checks'
    parts.append(stat(checks))
    for d in sorted(os.listdir(checks)) if checks.is_dir() else []:
        parts.append(stat(checks / d))
    parts.append(stat(STATE_DIR / 'attempts'))
    parts.append(stat(ROOT / 'state/repairs'))
    for directory in ('lift', 'accessory-lift', 'tooling-font', 'call-abi', 'sdkimport', 'repair-near95', 'seeds', 'cri', 'sourcealign', 'draftscan', 'spell'):
        # result stores are written whole by their commands: the store directory and its
        # entries change mtime when results land (a full walk visited 26,000 directories)
        top = STATE_DIR / directory
        parts.append(stat(top))
        try:
            for e in os.scandir(top):
                parts.append(f'{e.path}:{e.stat().st_mtime_ns}')
        except OSError:
            pass
    parts.append(stat(STATE_DIR / 'sweep_cache.json'))
    parts.append(str(max((r['id'] for r in []), default=0)))
    return hashlib.sha256('\n'.join(parts).encode()).hexdigest()


class SavedCandidates:
    def __init__(self, threshold, symbols=None):
        self.project, self.ledger = Project(), Ledger()
        self.threshold = threshold
        self.rows = {r['symbol']: dict(r) for r in self.ledger.db.execute(
            "SELECT * FROM functions WHERE status='unmatched'") if symbols is None or r['symbol'] in symbols}
        self.candidates = defaultdict(list)
        self.evidence = defaultdict(list)
        self.missing = []
        self.inputs = defaultdict(dict)
        self.unreadable = []
        try:
            self._sha = json.loads(SHA_CACHE.read_text()) if SHA_CACHE.exists() else {}
        except ValueError:
            self._sha = {}
        self._sha_dirty = False

    def _file_sha(self, path):
        """sha256 of a saved C file; saved files are content-addressed or append-only, so the
        digest is keyed by path alone."""
        key = str(path)
        sha = self._sha.get(key)
        if sha is None:
            sha = digest(path.read_text())
            self._sha[key] = sha
            self._sha_dirty = True
        return sha

    def add(self, symbol, record, origin):
        if symbol not in self.rows:
            return
        score = percent(record)
        if score > self.threshold:
            self.evidence[symbol].append(dict(origin=origin, percent=score))
        body = record.get('text') or record.get('body') or record.get('best_body')
        path = record.get('path')
        lazy = None
        if not body and isinstance(path, str) and path.endswith('.c'):
            path = Path(path)
            if not path.is_absolute():
                path = ROOT / path
            if str(path) in self._sha or path.is_file():
                lazy = path
        if lazy is not None:
            try:
                sha = record['sha256'] if record.get('sha256') else self._file_sha(lazy)
            except OSError:
                lazy = None
        if lazy is None and (not isinstance(body, str) or not body.strip()):
            if score > self.threshold:
                self.missing.append(dict(symbol=symbol, origin=origin, percent=score))
            return
        if lazy is None:
            sha = digest(body)
            if record.get('sha256') and record['sha256'] != sha:
                raise ValueError(f'{origin}: saved candidate hash changed')
        self.inputs[sha[:24]][symbol] = LazyRecord(body=body, original_path=str(lazy) if lazy else None)
        if score <= self.threshold:
            return
        self.candidates[symbol].append(LazyRecord(
            body=body, percent=score, sha256=sha, origin=origin,
            **{k:record[k] for k in ('raw_percent','percent_adjusted','aligned_word_percent','word_errors','differing_rows','instruction_rows') if k in record},
            original_path=str(path) if path else None,
            mw=record.get('mw') or record.get('mw_version'),
            flags=record.get('flags') or record.get('extra_cflags'),
            settings_recorded=any(k in record for k in ('mw', 'mw_version', 'flags', 'extra_cflags'))))

    def walk(self, data, origin, symbol=None):
        if isinstance(data, dict):
            symbol = data.get('symbol', symbol)
            # SDK import records keep the oracle result beside the owned C path.
            record = {**data, **data.get('check', {})} if isinstance(data.get('check'), dict) else data
            if any(k in record for k in ('path', 'text', 'body', 'best_body')):
                self.add(symbol, record, origin)
            for key, value in data.items():
                if isinstance(value, (dict, list)) and key != 'check':
                    self.walk(value, f'{origin}/{key}', key if key in self.rows else symbol)
        elif isinstance(data, list):
            # Historical lift results embed the scored C, unlike generation checkpoints.
            if (len(data) == 5 and isinstance(data[0], str) and isinstance(data[1], int)
                    and isinstance(data[2], str) and isinstance(data[4], (float, int))):
                self.add(data[0].split('#')[0], dict(text=data[2], percent=data[4]), origin)
            else:
                for i, value in enumerate(data):
                    self.walk(value, f'{origin}/{i}', symbol)

    def collect(self):
        """Every store except the fixup reports is cached as one pickle keyed by a cheap
        fingerprint; reports (a new one lands with every engine run) are memoized per file."""
        import pickle
        key = _fingerprint(self.threshold, self.rows)
        cached = None
        if CACHE_PICKLE.exists():
            try:
                cached = pickle.loads(CACHE_PICKLE.read_bytes())
            except Exception:
                cached = None
        memo = cached.get('reports', {}) if cached else {}
        if cached and cached.get('key') == key:
            self.candidates, self.evidence, self.missing, self.inputs, self.unreadable = (
                defaultdict(list, cached['candidates']), defaultdict(list, cached['evidence']), list(cached['missing']),
                defaultdict(dict, cached['inputs']), list(cached['unreadable']))
        else:
            self._collect()
            tmp = CACHE_PICKLE.with_suffix('.tmp')
            tmp.write_bytes(pickle.dumps(dict(key=key, reports=memo, candidates=dict(self.candidates), evidence=dict(self.evidence),
                                              missing=self.missing, inputs=dict(self.inputs), unreadable=self.unreadable)))
            tmp.replace(CACHE_PICKLE)
        reports = []
        for directory, dirs, files in os.walk(STATE_DIR / 'fixup'):
            dirs[:] = [d for d in dirs if d not in ('objects', 'sources', 'declarations', 'probe')]
            if 'report.json' in files:
                reports.append(Path(directory) / 'report.json')
        changed = False
        for path in sorted(reports):
            st = os.stat(path)
            entry = memo.get(str(path))
            if not entry or entry[0] != (st.st_mtime_ns, st.st_size):
                data = json.loads(path.read_text())
                records = [dict(record, symbol=symbol) for symbol, record in data.get('best', {}).items()]
                records.extend(data.get('records', []))
                keep = ('symbol', 'percent', 'raw_percent', 'percent_adjusted', 'adjusted', 'best', 'score', 'source', 'sha256',
                        'mw', 'mw_version', 'flags', 'extra_cflags', 'aligned_word_percent', 'word_errors', 'differing_rows', 'instruction_rows')
                lite = [{k: r[k] for k in keep if k in r} for r in records if 'percent' in r and 'symbol' in r and r.get('source')]
                entry = ((st.st_mtime_ns, st.st_size), lite)
                memo[str(path)] = entry
                changed = True
            for record in entry[1]:
                # only candidates above the threshold matter here; replaying every low
                # variant of every report cost 11 s per engine start
                if percent(record) > self.threshold:
                    self.add(record['symbol'], {**record, 'path': record['source']}, str(path.relative_to(ROOT)))
        if self._sha_dirty:
            SHA_CACHE.write_text(json.dumps(self._sha))
        if changed:
            try:
                cached = pickle.loads(CACHE_PICKLE.read_bytes())
                cached['reports'] = memo
                tmp = CACHE_PICKLE.with_suffix('.tmp')
                tmp.write_bytes(pickle.dumps(cached))
                tmp.replace(CACHE_PICKLE)
            except Exception:
                pass

    def _collect(self):
        for symbol in self.rows:
            index = STATE_DIR / 'checks' / symbol.replace(':', '__') / 'index.jsonl'
            if index.exists():
                for line in index.read_text().splitlines():
                    record = json.loads(line)
                    self.add(symbol, {**record, 'path': str(index.parent / f"{record['n']:03d}.c")},
                             f'{index.relative_to(ROOT)}:{record["n"]}')
        for row in self.ledger.db.execute('SELECT * FROM attempts ORDER BY id'):
            if row['symbol'] not in self.rows:
                continue
            record = dict(percent=max(row['best_in_attempt'] or 0, row['final_percent'] or 0),
                          path=row['best_body_path'])
            metadata = Path(row['best_body_path']).with_suffix('.json') if row['best_body_path'] else None
            if metadata and metadata.exists():
                record.update(json.loads(metadata.read_text()))
            self.add(row['symbol'], record, f'ledger:attempt/{row["id"]}')

        # The unified fixup reports are applied by collect() after this base state, memoized per file.

        for path in sorted((ROOT/'state/repairs').glob('*.json.gz')):
            data=json.loads(gzip.decompress(path.read_bytes()))
            # Source archives are portable; allocator captures use another
            # schema and contain no directly ranked C records.
            for record in data.get('records',[]):
                if isinstance(record,dict) and record.get('symbol') and record.get('body'):
                    self.add(record['symbol'],record,str(path.relative_to(ROOT)))

        # Only compile-result stores: donor discovery/fuzzy scores measure opcode
        # similarity, not how closely an owned C reconstruction compiles.
        paths = set()
        for directory in ('lift', 'accessory-lift', 'tooling-font', 'call-abi', 'sdkimport',
                          'repair-near95', 'seeds', 'cri'):
            paths.update((STATE_DIR / directory).rglob('*.json'))
        paths.update((STATE_DIR / 'sourcealign' / name) for name in
                     ('imports.json', 'matches.json', 'rechecked.json'))
        for path in sorted(paths):
            if path.exists():
                if path.name == 'context.json':
                    continue  # Old context dumps are Markdown despite their suffix.
                try:
                    data = json.loads(path.read_text())
                except ValueError as error:
                    self.unreadable.append(dict(path=str(path.relative_to(ROOT)), error=str(error)))
                    continue
                self.walk(data, str(path.relative_to(ROOT)))

        path = STATE_DIR / 'draftscan/scores.json'
        if path.exists():
            for symbol, module, size, score, label in json.loads(path.read_text()):
                self.add(symbol, dict(percent=score, path=str(path.parent / f'{module}__{symbol}.c')),
                         f'{path.relative_to(ROOT)}:{symbol}')
        path = STATE_DIR / 'spell/results.json'
        if path.exists():
            for symbol, module, size, base, result in json.loads(path.read_text())['results']:
                source = path.parent / symbol.replace(':', '__') / ('winner.c' if result['matched'] else 'best.c')
                if not source.exists() and not result.get('path'):
                    # No rewrite: spell deliberately omits best.c for its input.
                    source = STATE_DIR / 'sweep' / (symbol.replace(':', '__') + '.c')
                self.add(symbol, dict(percent=result.get('best') or 0, path=str(source)),
                         f'{path.relative_to(ROOT)}:{symbol}')

        # Sweep cache keys bind scores to the input body hash; repairs may also
        # retain an improved body. Recover their symbols from indexed inputs.
        path = STATE_DIR / 'sweep_cache.json'
        if path.exists():
            for key, record in json.loads(path.read_text()).items():
                if percent(record) <= self.threshold:
                    continue
                for symbol, original in list(self.inputs.get(key.split(':')[-1], {}).items()):
                    body = record.get('body') or original['body']
                    self.add(symbol, {**record, 'body': body}, f'{path.relative_to(ROOT)}:{key}')

        # Before check archives existed, crashes could leave .best.c without an
        # attempt body_path. Keep ledger eligibility, then check that saved body.
        for symbol, row in self.rows.items():
            if row['best_percent'] > self.threshold:
                self.evidence[symbol].append(dict(origin='ledger:function', percent=row['best_percent']))
                if not self.candidates[symbol]:
                    self.add(symbol, dict(percent=row['best_percent'],
                                          path=str(STATE_DIR / 'attempts' / f'{symbol}.best.c')),
                             'ledger:function/best-body-fallback')


def refine(saved, output, manifest, threshold):
    pending = defaultdict(list)
    for symbol, seed in manifest.items():
        if seed['current_percent'] > threshold:
            continue
        seen = {(seed['sha256'], seed['mw'], seed['flags'])}
        for record in saved.candidates[symbol]:
            key = (record['sha256'], record['mw'], record['flags'])
            if key in seen:
                continue
            seen.add(key)
            pending[symbol].append(record)
    trials = []
    while any(pending.values()):
        groups = defaultdict(list)
        candidates = {}
        for symbol, records in pending.items():
            if not records:
                continue
            record = records.pop()
            path = output / 'alternates' / (symbol.replace(':', '__') + '.c')
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(record['body'])
            candidates[symbol] = record
            groups[(record['mw'], record['flags'])].append((symbol, path))
        for (mw, flags), items in groups.items():
            for symbol, result in oracle.check_many(saved.project, items, 0, mw, flags).items():
                score = max(result.percent, result.percent_adjusted) if result.ok else 0
                record = candidates[symbol]
                trials.append(dict(symbol=symbol, sha256=record['sha256'], origin=record['origin'],
                                   percent=score, mw=result.mw_version, flags=result.extra_cflags))
                if score <= manifest[symbol]['current_percent']:
                    continue
                manifest[symbol].update({k: v for k, v in record.items() if k != 'body'})
                manifest[symbol].update(current_percent=score, current_error=None,
                                        mw=result.mw_version or mw, flags=result.extra_cflags or flags)
                Path(manifest[symbol]['path']).write_text(record['body'])
        print(f'checked {len(trials)} alternate saved candidates', flush=True)
    (output / 'alternates.json').write_text(json.dumps(trials, indent=2) + '\n')


def prepare(output: Path, threshold: float):
    if (output / 'manifest.json').exists():
        raise ValueError(f'{output}: frozen manifest already exists; use a new directory')
    saved = SavedCandidates(threshold)
    saved.collect()
    output.mkdir(parents=True, exist_ok=True)
    manifest, stale, missing = {}, [], []
    for symbol in sorted(saved.evidence, key=lambda s: (-saved.rows[s]['size'], s)):
        sym = saved.project.resolve(symbol)
        if sym is None:
            stale.append(symbol)
            continue
        records = saved.candidates[symbol]
        if not records:
            missing.append(symbol)
            continue
        # Check archives supply compiler settings for byte-identical old attempts.
        options = {r['sha256']: r for r in records if r['settings_recorded']}
        for r in records:
            if not r['settings_recorded'] and r['sha256'] in options:
                r.update({k: options[r['sha256']][k] for k in ('mw', 'flags', 'settings_recorded')})
        best = max(records, key=lambda r: (r['percent'], r['settings_recorded'], r['origin'].startswith('.fzgx/checks/')))
        path = output / (symbol.replace(':', '__') + '.c')
        path.write_text(best['body'])
        manifest[symbol] = {k: v for k, v in best.items() if k != 'body'}
        manifest[symbol].update(path=str(path.resolve()), size=sym.size, module=sym.module,
                                kind='recovered', ledger_percent=saved.rows[symbol]['best_percent'])
    audit = dict(threshold=threshold, comparison='>', size_cap=None, sdk_excluded=False,
                 functions=len(manifest), bytes=sum(r['size'] for r in manifest.values()),
                 ledger_above_threshold=sum(r['best_percent'] > threshold for r in saved.rows.values()),
                 additional_to_ledger=[s for s in manifest if saved.rows[s]['best_percent'] <= threshold],
                 evidence=dict(saved.evidence), stale=stale, missing=missing,
                 records_without_body=saved.missing, unreadable=saved.unreadable)
    (output / 'selection.json').write_text(json.dumps(audit, indent=2) + '\n')
    if missing:
        raise ValueError(f'{len(missing)} eligible functions have no saved body: {missing}')

    # The historical threshold determines membership. Rechecking freezes usable
    # compiler settings and exposes stale declarations without silently dropping C.
    groups = defaultdict(list)
    for symbol, record in manifest.items():
        groups[(record['mw'], record['flags'])].append((symbol, Path(record['path'])))
    checked = 0
    for (mw, flags), items in groups.items():
        for symbol, result in oracle.check_many(saved.project, items, 0, mw, flags).items():
            record = manifest[symbol]
            record['current_percent'] = max(result.percent, result.percent_adjusted) if result.ok else 0
            record['current_error'] = result.error if not result.ok else None
            record['mw'] = result.mw_version or mw
            record['flags'] = result.extra_cflags or flags
        checked += len(items)
        print(f'checked {checked}/{len(manifest)} saved candidates', flush=True)
    refine(saved, output, manifest, threshold)
    (output / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    summary = {k: audit[k] for k in ('functions', 'bytes', 'ledger_above_threshold', 'stale')}
    summary.update(additional_to_ledger=len(audit['additional_to_ledger']),
                   current_above_threshold=sum(r['current_percent'] > threshold for r in manifest.values()),
                   compile_errors=sum(bool(r['current_error']) for r in manifest.values()),
                   min_size=min(r['size'] for r in manifest.values()), max_size=max(r['size'] for r in manifest.values()),
                   manifest=str(output / 'manifest.json'))
    (output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    return summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--above', type=float, default=90)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(prepare(args.output.resolve(), args.above)), flush=True)


if __name__ == '__main__':
    main()
