# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

FdF — a 42 school wireframe (heightmap) renderer in C using MiniLibX/X11, on branch
`release/v1.0`. Beyond the mandatory part it carries a large bonus layer: animated
backgrounds, particle systems, textures, themes, shape morphing (torus/cube/DNA/heart/…),
trackball rotation, and a dance system. Tuned for large maps (multi-million points).

## Build & run

```sh
make              # parallel by default (-j nproc), -O3 -march=native -flto -ffast-math
make re           # full rebuild (also rebuilds libft)
make debug        # fclean + rebuild with -O0 -g3 -fsanitize=address,undefined
make norminette   # 42 norm check (excludes minilibx + libft submodule)
./fdf test_maps/42.fdf        # exactly one map argument
```

- Libraries: libft is a git submodule at `include/libft` (builds to
  `include/libft/build/lib/libft.a`; run `git submodule update --init` after clone).
  MiniLibX is vendored at `include/lib/minilibx-linux`.
- Sources are glob-discovered (`find sources -name '*.c'`) — new files need no
  Makefile edit. Dependency tracking via `-MMD` — header edits rebuild dependents.
- `-ffast-math` is safe here (verified: no NaN/inf checks in the codebase).
- Window size: `-DWIN_WIDTH=... -DWIN_HEIGHT=...`.

## Benchmark & verification

```sh
tools/bench.sh [frames]        # per-stage ms across map sizes, headless (Xvfb)
FDF_BENCH=120 ./fdf map.fdf    # one run: prints per-stage table, exits cleanly
python3 tools/genmap.py W H --color > map.fdf   # synthetic terrain generator
tools/check_maps.sh            # edge-case gate: malformed maps must fail cleanly
```

`FDF_BENCH` forces auto-rotate (measures the moving pipeline) and bypasses the
idle-skip. Env selectors for demos/tests: `FDF_BG=<0..12>` dynamic background
(12 = black hole), `FDF_SHAPE=<0..16>` morph target at launch, `FDF_VIEW=<0..2>`
render mode (0 wire, 1 solid, 2 solid+wire; M key cycles at runtime),
`FDF_CAM=1` first-person camera (F toggles; WASD move, QE up/down, arrows or
right-drag look). FPS-cam solid: 250k-pt map ~58 FPS, 1M grazing view ~26 FPS.
Reference numbers (2920x2000 window, Xvfb): 1000x1000 map ≈ 4.0 ms/frame wire
(~250 FPS) and ≈ 5.9 ms solid (~170 FPS); 3000x1500 (4.5M points) ≈ 7.9 ms;
parse of 4.5M points ≈ 107 ms; black-hole scene ≈ 9.4 ms; procedural
backgrounds 4–7 ms (quarter-res + upscale).
Valgrind is clean (0 errors, no leaks) on parse→render→exit; keep it that way.

## Architecture

Frame flow: `main.c` → `make_fdf()` (parse map → init mlx → transform stack → event
bindings) → `mlx_loop()` → `fdf_render()` per frame: animation-system updates →
`transform_points` (inlined 4x4 multiply, vectorizable flat loop) → background fill →
`fdf_draw_lines` → particles → `mlx_put_image_to_window`.

Performance machinery (do not regress):
- **Idle skip**: `fdf_render` returns immediately (+`usleep`) unless `needs_redraw`
  is set or an animation system is active. Every input handler sets
  `f->needs_redraw = true`; the Expose hook does too. Static scenes cost ~0% CPU.
- **Stride LOD** (`grid_stride` in `fdf_draw_lines.c`): when projected grid spacing
  is sub-pixel, the grid is walked with a stride — visually identical, edge count
  drops by stride². There is no edge array; topology is the implicit grid.
- **Fixed-point Bresenham** (`bresenham_lines.c`): 12.20 integer color accumulators;
  per-line setup uses a reciprocal table instead of divisions
  (`init_bresenham.c`); solid / gradient / guarded loop variants; degenerate
  edges (same pixel) short-circuit to a single plot.
- **Background** is a `wmemset` fill (memory-bandwidth-bound, ~1.4 ms at 2920x2000 —
  the FPS ceiling for small maps).
- **Black-hole scene** (dynamic bg mode 12, `render/background/black_hole*.c`):
  point-lens LUT precomputed once (screen pixel → star-texture coord or ring
  palette sentinel), per frame one indirection per pixel; the starfield drifts
  by offsetting the source column. `black_hole_warp_points` bends vertices in
  NDC toward the hole. Writes straight to the framebuffer (skips bg_buffer).
  Tunables are the `BH_*` macros in config.h.

More machinery:
- **Rasterizer** (`sources/raster/`): solid-surface mode — two flat-shaded
  triangles per (strided) grid cell, incremental edge-function fill with a
  float z-buffer (`zbuffer.c`, +INF-cleared via wmemset), per-vertex Lambert
  shade precomputed once from heightmap normals (`lighting.c`).
- **Transitions** (`transition_fast.c`): shape positions are trig-heavy, so
  they are computed once per transition into src/dst clouds; every frame is a
  fused lerp + 4x4 transform. Persistent shapes replay the dst cloud. 17
  shapes total (torus…tube + mobius/knot/galaxy/helix/klein/vortex); adding
  one = one `pos_*()` in `animation/` + enum + table entry.
- **Backgrounds** render at BG_W x BG_H (quarter res, `bg_upscale.c` expands
  4x4 blocks) — 10-12x faster; the black hole writes full-res directly.
- **First-person camera** (`raster/camera*.c`, `project.c`): perspective *
  view matrix overwrites `trans_stack.combined` each frame, so every pipeline
  (grid, morphs) works in FPS mode; transformed_points then holds CLIP coords,
  divided + near-clipped per edge/triangle (`edge_project`). Anisotropic
  distance LOD (`fdf_row_stride`): row stride explodes at the foreshortened
  horizon, killing overdraw. Sky (`sky.c`) is baked once (gradient + sun);
  fog blends toward the horizon color by view distance; terrain cast shadows
  are ray-marched over the heightfield once and baked into the vertex shade.
- **Resizable window** (`raster/viewport.c`): mlx pins WM min=max size hints;
  viewport_init re-issues sane ones so edge-drag resize works. The
  framebuffer stays WIN_WIDTH x WIN_HEIGHT (max, stride unchanged); rendering
  targets the runtime `gviewport()` size and X clips the rest. Size is polled
  every 8th frame (mlx never dispatches ConfigureNotify); sky + black-hole
  LUT rebuild once the size settles. F11 cycles full / two-thirds / half
  presets. Window max = compile-time WIN_* (raise those to go bigger).
- **Particles** (`animation/particle_*.c`, `render/particles/`): 2048 max,
  wall-clock dt integration (`ps_delta`, frame-rate independent), soft radial
  sprites with alpha blending, additive blending for fire/sparks/stars,
  velocity-aligned rain streaks, per-type physics (flutter/buoyancy/bounce),
  lifetime fades, fire color ramp, depth-layer parallax in `p->z`.
  `FDF_PART=<1..8>` selects a type at launch.
- **Black hole ↔ object**: `black_hole_warp_points` applies the point-lens
  primary-image equation to vertices (aspect-corrected), so the wireframe
  wraps around the Einstein ring instead of crossing the hole.

Source layout (`sources/`): `core/` (main, bootstrap), `parser/` (chunked .fdf
reader; short rows are padded, over-long rows rejected), `algorithms/` (matrix +
line rasterization), `transform/` (matrix stack, projections, shapes, effects,
z-scale), `events/` (table-driven dispatch: `handler_table[keycode][modifiers]`;
actions in `stub_event/`), `animation/` (transition/particle/dance/texture/dyn-bg
drivers), `render/` (frame composition, `background/`, `particles/`, `textures/`,
`theme/`, `writer/` bitmap font), `helpers/` (cleanup, singletons, bench).

Headers live in `include/`. `fdf.h` is the master prototype header; `fdf_ds.h` holds
all structs (guard `FDF_DS_H`; the name avoids colliding with libft's `ds.h`/`DS_H`).
`pixel.h`, `quaternion.h`, `matrices.h` are fdf-owned geometry headers (ported from
the old vendored libft — the submodule libft does not provide geometry types).

Key patterns to preserve:
- **No globals — singleton accessors**: mutable shared state lives in `static`
  locals behind `g*()` functions (`gdance()`, `gtrack()`, `gbench()`, …). Animation
  subsystems expose `*_update() / *_toggle() / *_is_active() / *_cleanup()`.
- **Norminette-shaped code**: ≤25-line functions, ≤4 params, ≤5 vars, ≤5 functions
  per file, no typedef in `.c`, header guard = filename. Run `make norminette` on
  touched files before calling work done.
- The parse/render/exit path must stay valgrind-clean; bench mode exits through
  `mlx_loop_end` → `fdf_destroy_contents`, so leaks show up immediately.
