/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCH_H
# define BENCH_H

# include <stdint.h>
# include "fdf_ds.h"

/*
** Frame-stage profiler, active only when FDF_BENCH=<frames> is set in the
** environment. Zero work otherwise (one cached branch per lap).
** After <frames> frames it prints a per-stage table to stderr and exits
** cleanly through mlx_loop_end.
*/

typedef enum e_bench_stage
{
	BS_ANIM,
	BS_TRANSFORM,
	BS_FX,
	BS_BG,
	BS_LINES,
	BS_PARTICLES,
	BS_PRESENT,
	BS_COUNT
}	t_bench_stage;

typedef struct s_bench
{
	uint64_t	acc[BS_COUNT];
	uint64_t	last;
	uint64_t	parse_ns;
	int			frames;
	int			target;
	bool		init;
}	t_bench;

t_bench		*gbench(void);
uint64_t	bench_now_ns(void);
int			bench_active(void);
void		bench_begin(void);
void		bench_lap(int stage);
void		bench_parse(uint64_t ns);
void		bench_frame(t_app *f);

#endif
