#!/bin/sh
# tools/capture/capture132.sh SYMBOL BODY.c MODULE  -> coloring-only GC/1.3.2 capture in $FZGX_CAPTURE_DIR/SYMBOL
set -eu
SYM=$1; BODY=$2; MODULE=$3
ROOT=/Users/rayan/fzgx
OUT=${FZGX_CAPTURE_DIR:-$ROOT/.fzgx/capture}/$SYM
mkdir -p "$OUT"; cp "$BODY" "$OUT/$SYM.c"
uv run python -c "
import sys; sys.path.insert(0,'tools')
from fzgx.project import Project; from fzgx import oracle
print(oracle.module_flags(Project(),'$MODULE')[0] + ' ' + '${EXTRA_FLAGS:-}')" > "$OUT/flags.txt"
cat > "$OUT/capture.gdb" <<GDB
set pagination off
set confirm off
python
import sys
sys.path.append('/Users/rayan/mwcc/tools')
sys.path.append('/Users/rayan/fzgx/tools/capture')
end
target remote :1234
source /Users/rayan/fzgx/tools/capture/mwcc132_snapshot.py
mwcc132-capture $OUT
continue
quit
GDB
cat > "$OUT/run.sh" <<RUN
#!/bin/sh
set -u
cd $ROOT; mkdir -p /tmp/wibo; export HOME=/tmp WIBO_TMP_DIR=/tmp/wibo
eval set -- \$(cat $OUT/flags.txt)
qemu-i386 -g 1234 /Users/rayan/mwcc/build/tools/wibo-i686 build/compilers/GC/1.3.2/mwcceppc.exe "\$@" -c $OUT/$SYM.c -o $OUT/$SYM.o > $OUT/compile.log 2>&1 &
Q=\$!; sleep 2; gdb-multiarch -batch -x $OUT/capture.gdb > $OUT/gdb.log 2>&1; wait \$Q; echo "compile exit \$?" >> $OUT/compile.log
RUN
limactl shell fzgx-capture -- sh "$OUT/run.sh"
grep -v "^Reading\|^warning\|^0x\|^\[Inferior" "$OUT/gdb.log" | tail -8; ls "$OUT" | grep -c json
