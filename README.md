# FdF — wireframe renderer turned tiny 3D engine

A 42 school heightmap renderer (C, MiniLibX/X11) pushed far beyond the subject:
a software rasterizer with z-buffer and lighting, a first-person camera, a
gravitationally-lensed black hole, 17 morphable shapes, a physically-animated
particle system, and a benchmarked rendering pipeline that draws a **4.5
million point map at ~130 FPS** and parses it in ~107 ms.

![view modes](https://img.shields.io/badge/modes-wire%20%7C%20solid%20%7C%20first--person-blue)

## Build

```sh
git clone --recursive <repo>        # libft is a submodule (include/libft)
# or, after a plain clone:
git submodule update --init

make              # parallel by default, -O3 -march=native -flto -ffast-math
make re           # full rebuild (including libft)
make debug        # -O0 -g3 -fsanitize=address,undefined
make norminette   # 42 norm check (excludes minilibx + libft)
```

MiniLibX is vendored (`include/lib/minilibx-linux`); you need the usual X11
dev packages (`libx11-dev`, `libxext-dev`).

## Run

```sh
./fdf test_maps/42.fdf                          # exactly one map argument
python3 tools/genmap.py 1000 1000 --color > big.fdf   # synthetic terrain
./fdf big.fdf
```

Map format: rows of integer heights, optional `,0xRRGGBB` per point.
Short rows are padded; malformed maps exit cleanly with an error.

## Controls

| Key | Action |
|---|---|
| `W A S D` | move model — or fly (forward/strafe) in camera mode |
| Arrows | rotate model — or look around in camera mode |
| Left-drag / Right-drag | pan / rotate — mouse-look in camera mode |
| Scroll | zoom |
| `F` | **first-person camera** on/off (free flight, `Q`/`E` down/up) |
| `M` | view mode: wireframe → solid surface → solid + wire |
| `T` | morph to the next shape (17: torus, sphere, cube, pyramid, DNA, chips, wave, heart, cone, tube, Möbius, trefoil knot, galaxy, helix, Klein bottle, vortex) |
| `B` | dynamic background (13 modes, `12` = black hole) |
| `G` | particle system (snow, rain, fire, sparks, stars, bubbles, dust, smoke) |
| `V` | animated texture (12, crossfades on switch) |
| `H` | object effects (vertex wave, pulse, twist… works on morphed shapes) |
| `Z` | dance system |
| `1`–`9` | color palettes |
| `I` / `P` | isometric / fly projection |
| `Space` | auto-rotate |
| `F11` | window size presets: full screen → ⅔ → half |
| drag window edges | live resize (scene rescales, baked buffers rebuild) |
| `+` / `-` | zoom; `Ctrl`+arrows: z-scale |
| `R` | reset |
| `Esc` | quit |

## Environment selectors (demos & scripting)

Every subsystem can be pre-selected at launch:

```sh
FDF_CAM=1 FDF_VIEW=1 ./fdf big.fdf        # first-person over solid terrain
FDF_BG=12 FDF_PART=1 ./fdf map.fdf        # snowstorm feeding the black hole
FDF_SHAPE=12 FDF_FX=4 ./fdf map.fdf       # spiral-twisted galaxy morph
FDF_BENCH=120 ./fdf map.fdf               # 120 frames, per-stage ms table, exit
```

| Variable | Meaning |
|---|---|
| `FDF_VIEW=0..2` | wireframe / solid / solid+wire |
| `FDF_CAM=1` | start in first-person camera |
| `FDF_SHAPE=0..16` | morph into that shape at launch |
| `FDF_BG=0..12` | dynamic background (12 = black hole) |
| `FDF_PART=1..8` | particle type |
| `FDF_FX=1..9` | object effect |
| `FDF_BENCH=N` | benchmark N frames and exit (forces auto-rotate) |

## Benchmarks

```sh
tools/bench.sh [frames]     # headless (Xvfb) sweep across map sizes
tools/check_maps.sh         # edge-case gate: bad maps must fail cleanly
```

Reference numbers (2920×2000 window, Xvfb, moving pipeline):

| Scene | Frame time | FPS |
|---|---|---|
| 1000×1000 map, wireframe | 4.0 ms | ~250 |
| 1000×1000 map, solid + lighting | 5.9 ms | ~170 |
| 3000×1500 map (4.5M points) | 7.9 ms | ~127 |
| Black-hole scene (full lensing) | 9.4 ms | ~106 |
| Animated backgrounds | 4–7 ms | 140–240 |
| Parse 4.5M points | 107 ms | once |

Valgrind is clean (0 errors, 0 leaks) on parse → render → exit, including
the black-hole, camera, particle, and resize paths.

## What's inside

- **Fast wireframe core** — fixed-point (12.20) Bresenham with a reciprocal
  table instead of divisions, implicit grid topology (no edge array), and a
  stride LOD that skips sub-pixel geometry: visually identical, edge count
  drops with the square of the stride. Idle frames cost ~0% CPU (dirty-flag
  skip; input wakes the loop instantly).
- **Software rasterizer** (`sources/raster/`) — two flat-shaded triangles per
  grid cell, incremental edge-function fill, float z-buffer, per-vertex
  Lambert lighting from heightmap normals, and heightfield ray-marched
  **cast shadows** — all baked once, zero per-frame lighting cost.
- **First-person camera** — perspective × view matrix slots into the same
  transform pipeline (morphs work in FPS mode too), clip-space near-plane
  clipping, anisotropic distance LOD (row stride explodes at the
  foreshortened horizon), gradient sky with an emissive sun, distance fog.
- **Black hole** (`FDF_BG=12`) — screen-space point-lens: a precomputed LUT
  bends a drifting starfield around the hole (Einstein-ring inversion
  included), photon ring with relativistic beaming, and the **wireframe
  itself is lensed** around the ring. Particles feel its gravity and are
  absorbed past the photon sphere.
- **Ultra-fast morphs** — shape positions are trig-heavy, so they're baked
  once per transition into point clouds; every frame is a fused
  lerp + 4×4 transform (~1.8 ms for 1M points). 18-frame transitions.
- **Particles** — up to 2048, wall-clock Δt physics (frame-rate independent),
  soft alpha sprites + additive glow, motion-blur rain streaks, fire color
  ramp, spark ground-bounce, depth-layer parallax.
- **Resizable window** — drag the edges; the scene rescales live. The
  framebuffer stays at the compile-time maximum so hot loops never change;
  window size beyond that: rebuild with `-DWIN_WIDTH=... -DWIN_HEIGHT=...`.

## Layout

```
sources/
  core/        main, bootstrap          algorithms/  matrix + Bresenham + LOD
  parser/      chunked .fdf reader      raster/      triangles, z-buffer, light,
  transform/   matrix stack, effects                 camera, sky, viewport
  events/      table-driven input       animation/   morphs, particles, dance,
  render/      frame composition,                    textures, dynamic bg
               backgrounds, particles,  helpers/     singletons, cleanup, bench
               textures, themes
```

Architecture details and invariants: see `CLAUDE.md`.
