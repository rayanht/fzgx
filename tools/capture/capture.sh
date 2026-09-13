#!/bin/sh
# Capture MWCC's PCode and register-coloring state for one function of a per-function body.
#   tools/capture/capture.sh SYMBOL BODY.c MODULE [GC/1.2.5n|GC/1.2.5] [FUNCTION_INDEX]
# Runs inside the `fzgx-capture` Lima VM (tools/capture/fzgx-capture.yaml): qemu-i386 executes
# the i386 wibo from the recovery project with the stock compiler under a GDB stub, and the
# recovery project's tools/gdb/allocator_snapshot.py writes every PCode stage, the coloring
# graph before/after selection, creation events and the stack-frame home list to
# .fzgx/capture/SYMBOL/. Only the 1.2.5 / 1.2.5n address set is known to the capture scripts.
# Read the result with `python3 /Users/rayan/mwcc/tools/vreg_map.py .fzgx/capture/SYMBOL 0001`
# and replay it with `python3 /Users/rayan/mwcc/tools/replay/simplify_replay.py DIR 0001`.
set -eu
SYM=$1; BODY=$2; MODULE=$3; MW=${4:-GC/1.2.5n}; IDX=${5:-1}
ROOT=/Users/rayan/fzgx
OUT=${FZGX_CAPTURE_DIR:-$ROOT/.fzgx/capture}/$SYM  # the VM mounts the repo read-only; point this at a writable mount
mkdir -p "$OUT"
cp "$BODY" "$OUT/$SYM.c"
uv run python -c "
import sys; sys.path.insert(0,'tools')
from fzgx.project import Project; from fzgx import oracle
print(oracle.module_flags(Project(),'$MODULE')[0] + ' ' + '${EXTRA_FLAGS:-}')" > "$OUT/flags.txt"
TARGET=stock; case "$MW" in *n) TARGET=ninji;; esac
cat > "$OUT/capture.gdb" <<GDB
set pagination off
set confirm off
python
import sys
sys.path.append('/Users/rayan/mwcc/tools')
sys.path.append('/Users/rayan/mwcc/tools/gdb')
end
target remote :1234
source /Users/rayan/mwcc/tools/gdb/allocator_snapshot.py
mwcc-auto-capture $OUT $IDX $TARGET
continue
quit
GDB
cat > "$OUT/run.sh" <<RUN
#!/bin/sh
set -u
cd $ROOT
mkdir -p /tmp/wibo
export HOME=/tmp WIBO_TMP_DIR=/tmp/wibo
eval set -- \$(cat $OUT/flags.txt)
qemu-i386 -g 1234 /Users/rayan/mwcc/build/tools/wibo-i686 build/compilers/$MW/mwcceppc.exe "\$@" -c $OUT/$SYM.c -o $OUT/$SYM.o > $OUT/compile.log 2>&1 &
QPID=\$!
sleep 2
gdb-multiarch -batch -x $OUT/capture.gdb > $OUT/gdb.log 2>&1
wait \$QPID
echo "compile exit \$?" >> $OUT/compile.log
RUN
limactl shell fzgx-capture -- sh "$OUT/run.sh"
tail -3 "$OUT/gdb.log"
ls "$OUT" | grep -c json
