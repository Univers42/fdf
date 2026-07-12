/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_fast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

/*
 * Shape positions are trig-heavy, so they are computed exactly ONCE per
 * transition into two point clouds (src and dst). Every frame after that
 * is a fused lerp + 4x4 transform: no trig, no per-point function call,
 * vectorizable. Persistent shapes replay the dst cloud (t = 0 on dst).
 */

static void	fill_shape_cloud(t_app *f, t_shape_type shape, float *buf)
{
	t_point2	p;
	t_fpoint3	out;

	p.y = -1;
	while (++p.y < f->height)
	{
		p.x = -1;
		while (++p.x < f->width)
		{
			get_shape_position(shape, f, &p, &out);
			buf[0] = out.x;
			buf[1] = out.y;
			buf[2] = out.z;
			buf += 3;
		}
	}
}

bool	transition_prepare(t_app *f)
{
	t_transition_state	*st;
	size_t				n;

	st = gtransition(NULL);
	n = sizeof(float) * 3u * (size_t)(f->width * f->height);
	if (!st->cloud_src)
		st->cloud_src = (float *)malloc(n);
	if (!st->cloud_dst)
		st->cloud_dst = (float *)malloc(n);
	if (!st->cloud_src || !st->cloud_dst)
		return (false);
	fill_shape_cloud(f, st->current_shape, st->cloud_src);
	fill_shape_cloud(f, st->target_shape, st->cloud_dst);
	return (true);
}

/*
 * Live per-frame systems (object effects, dance) mutate f->points; the
 * clouds were baked from the unperturbed map, so the current delta is
 * re-applied on top — H-key effects stay visible on morphed shapes.
 */
static void	fx_offsets(t_app *f, const float **off, const float **base)
{
	*off = NULL;
	*base = NULL;
	if (object_effects_is_active() && gobjfx(NULL)->original_points)
	{
		*off = f->points;
		*base = gobjfx(NULL)->original_points;
	}
}

void	transition_transform(t_app *f, const float *a, const float *b, float t)
{
	const float	*m;
	const float	*ob[2];
	float		*dp;
	float		p[3];
	int			i;

	m = f->trans_stack.combined;
	fx_offsets(f, &ob[0], &ob[1]);
	dp = (float *)f->transformed_points;
	i = -1;
	while (++i < f->width * f->height)
	{
		p[0] = a[0] + (b[0] - a[0]) * t;
		p[1] = a[1] + (b[1] - a[1]) * t;
		p[2] = a[2] + (b[2] - a[2]) * t;
		if (ob[0])
			p[2] += ob[0][i] - ob[1][i];
		dp[0] = m[0] * p[0] + m[1] * p[1] + m[2] * p[2] + m[3];
		dp[1] = m[4] * p[0] + m[5] * p[1] + m[6] * p[2] + m[7];
		dp[2] = m[8] * p[0] + m[9] * p[1] + m[10] * p[2] + m[11];
		dp[3] = m[12] * p[0] + m[13] * p[1] + m[14] * p[2] + m[15];
		a += 3;
		b += 3;
		dp += 4;
	}
}
