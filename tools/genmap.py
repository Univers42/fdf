#!/usr/bin/env python3
"""Generate synthetic terrain .fdf maps for benchmarking.

usage: genmap.py WIDTH HEIGHT [--color] > out.fdf
Terrain = layered sines (continents + hills + crater ring), earth-like enough
to exercise the full z range and color gradients.
"""
import math
import sys


def main() -> None:
    w, h = int(sys.argv[1]), int(sys.argv[2])
    color = "--color" in sys.argv[3:]
    out = sys.stdout
    for y in range(h):
        row = []
        for x in range(w):
            z = (
                math.sin(x * 0.011 + y * 0.007) * 40
                + math.sin(x * 0.05) * math.cos(y * 0.05) * 18
                + math.sin(math.hypot(x - w / 2, y - h / 2) * 0.02) * 12
            )
            zi = int(z)
            if color:
                t = max(0.0, min(1.0, (zi + 70) / 140))
                r = int(40 + t * 215)
                g = int(80 + (1 - abs(t - 0.5) * 2) * 160)
                b = int(220 - t * 200)
                row.append(f"{zi},0x{r:02X}{g:02X}{b:02X}")
            else:
                row.append(str(zi))
        out.write(" ".join(row) + "\n")


if __name__ == "__main__":
    main()
