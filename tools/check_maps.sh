#!/bin/sh
# Edge-case gate: malformed maps must exit 1 fast; valid ones must run
# (timeout 124 = still rendering = pass for valid maps). Any other code
# (segfault 139, abort 134...) fails the gate.
set -e
cd "$(dirname "$0")/.."
make -s >/dev/null
D=$(mktemp -d)
trap 'rm -rf "$D"' EXIT

printf ''                              > "$D/empty.fdf"
printf '\n\n\n'                        > "$D/newlines.fdf"
printf 'abc def\n'                     > "$D/garbage.fdf"
printf '99999999999999999999 1\n2 3\n' > "$D/overflow.fdf"
printf '1,0xZZZ 2\n3 4\n'              > "$D/badcolor.fdf"
printf '1 2 3\n4 5\n'                  > "$D/ragged.fdf"
printf '5\n'                           > "$D/single.fdf"
printf '1 2\n3 4'                      > "$D/noeol.fdf"

expect() { # expect <code> <file>
	code=0
	timeout 4 xvfb-run -a ./fdf "$2" >/dev/null 2>&1 || code=$?
	if [ "$code" -ne "$1" ]; then
		echo "FAIL: $2 exited $code (expected $1)"; exit 1
	fi
	echo "ok: $(basename "$2") -> $code"
}

expect 1   /nonexistent.fdf
expect 1   "$D/empty.fdf"
expect 1   "$D/newlines.fdf"
expect 1   "$D/garbage.fdf"
expect 1   "$D/overflow.fdf"
expect 1   "$D/badcolor.fdf"
expect 124 "$D/ragged.fdf"
expect 124 "$D/single.fdf"
expect 124 "$D/noeol.fdf"
expect 124 test_maps/42.fdf
echo "all edge cases pass"
