#!/bin/sh
# Benchmark fdf across map sizes. usage: tools/bench.sh [frames]
# Runs headless under Xvfb; per-stage numbers printed by FDF_BENCH.
set -e
FRAMES=${1:-120}
cd "$(dirname "$0")/.."

make -s >/dev/null

gen() { [ -f "$2" ] || python3 tools/genmap.py "$1" "$1" --color > "$2"; }
gen 250  test_maps/gen_250.fdf
gen 500  test_maps/gen_500.fdf
gen 1000 test_maps/gen_1000.fdf

for map in test_maps/42.fdf test_maps/mars.fdf \
           test_maps/gen_250.fdf test_maps/gen_500.fdf test_maps/gen_1000.fdf; do
	echo "=== $map ==="
	FDF_BENCH=$FRAMES timeout 300 xvfb-run -a -s "-screen 0 3000x2100x24" \
		./fdf "$map" 2>&1 | grep "\[bench\]"
done
