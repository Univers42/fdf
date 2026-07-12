/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "bench.h"
#include <stdlib.h>
#include <time.h>

t_bench	*gbench(void)
{
	static t_bench	b;

	if (!b.init)
	{
		b.init = true;
		if (getenv("FDF_BENCH"))
			b.target = atoi(getenv("FDF_BENCH"));
	}
	return (&b);
}

int	bench_active(void)
{
	return (gbench()->target != 0);
}

uint64_t	bench_now_ns(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec);
}

void	bench_begin(void)
{
	t_bench	*b;

	b = gbench();
	if (!b->target)
		return ;
	b->last = bench_now_ns();
}

void	bench_lap(int stage)
{
	t_bench		*b;
	uint64_t	now;

	b = gbench();
	if (!b->target)
		return ;
	now = bench_now_ns();
	b->acc[stage] += now - b->last;
	b->last = now;
}
