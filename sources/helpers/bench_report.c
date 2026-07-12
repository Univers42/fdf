/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_report.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "bench.h"
#include <stdio.h>

void	bench_parse(uint64_t ns)
{
	gbench()->parse_ns = ns;
}

static void	bench_report(t_bench *b, t_app *f)
{
	static const char	*name[BS_COUNT] = {"anim", "transform", "fx",
		"background", "lines", "particles", "present"};
	uint64_t			total;
	int					i;

	total = 0;
	i = -1;
	while (++i < BS_COUNT)
		total += b->acc[i];
	fprintf(stderr, "[bench] map %dx%d points=%d edges=%zu parse=%.2fms\n",
		f->width, f->height, f->width * f->height, f->n_edges,
		(double)b->parse_ns / 1e6);
	i = -1;
	while (++i < BS_COUNT)
		fprintf(stderr, "[bench] %-10s %9.3f ms/f  %5.1f%%\n", name[i],
			(double)b->acc[i] / 1e6 / b->frames,
			100.0 * (double)b->acc[i] / (double)total);
	fprintf(stderr, "[bench] %-10s %9.3f ms/f  (%.1f FPS, %d frames)\n",
		"frame", (double)total / 1e6 / b->frames,
		1e9 * b->frames / (double)total, b->frames);
}

/*
 * Benchmarks force auto-rotate so the numbers measure the full moving
 * pipeline (transform + draw every frame), not the idle-skip path.
 */
void	bench_frame(t_app *f)
{
	t_bench	*b;

	b = gbench();
	if (!b->target)
		return ;
	if (b->frames == 0)
		f->auto_rotate = true;
	b->frames++;
	if (b->frames >= b->target)
	{
		bench_report(b, f);
		exit_prog(f, 0, NULL);
	}
}
