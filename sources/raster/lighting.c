/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

/*
 * Per-vertex Lambert shade from heightmap normals (central differences),
 * computed once per map against a fixed model-space light. The light
 * rides with the model as it rotates.
 * ponytail: static shade, recompute per frame with an inverse-rotated
 * light if world-fixed lighting is ever wanted.
 */

static int	iclamp(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static float	shade_at(t_app *f, int x, int y)
{
	float	d[2];
	float	len;
	float	dot;

	d[0] = f->points[y * f->width + iclamp(x + 1, 0, f->width - 1)]
		- f->points[y * f->width + iclamp(x - 1, 0, f->width - 1)];
	d[1] = f->points[iclamp(y + 1, 0, f->height - 1) * f->width + x]
		- f->points[iclamp(y - 1, 0, f->height - 1) * f->width + x];
	d[0] *= 0.5f;
	d[1] *= 0.5f;
	len = sqrtf(d[0] * d[0] + d[1] * d[1] + 1.0f);
	dot = (-d[0] * 0.42f - d[1] * -0.57f + 0.71f) / len;
	if (dot < 0.0f)
		dot = 0.0f;
	return (0.35f + 0.65f * dot);
}

/*
 * Cast shadows for a heightfield: march from the vertex toward the sun
 * (same direction as the Lambert light); if the terrain rises above the
 * ray, the vertex is in shadow. Baked once with the shade, so runtime
 * cost is zero. Slope is scaled to the map's own z-range.
 */
static float	shadow_at(t_app *f, int x, int y, float slope)
{
	float	p[3];
	int		i;
	int		gx;
	int		gy;

	p[0] = (float)x;
	p[1] = (float)y;
	p[2] = f->points[y * f->width + x];
	i = 0;
	while (++i < 48)
	{
		p[0] += 0.889f;
		p[1] += -1.208f;
		p[2] += 1.5f * slope;
		gx = (int)p[0];
		gy = (int)p[1];
		if (gx < 0 || gx >= f->width || gy < 0 || gy >= f->height)
			return (1.0f);
		if (f->points[gy * f->width + gx] > p[2] + 0.001f)
			return (0.45f);
	}
	return (1.0f);
}

float	*gshade(t_app *f)
{
	static float	*sh;
	float			slope;
	int				x;
	int				y;

	if (sh || !f)
		return (sh);
	sh = (float *)malloc(sizeof(float) * f->width * f->height);
	if (!sh)
		return (NULL);
	slope = (float)(f->max_z - f->min_z) * 4.0f
		/ fminf(f->width, f->height);
	if (slope < 0.05f)
		slope = 0.05f;
	y = -1;
	while (++y < f->height)
	{
		x = -1;
		while (++x < f->width)
			sh[y * f->width + x] = shade_at(f, x, y)
				* shadow_at(f, x, y, slope);
	}
	return (sh);
}

void	shade_free(void)
{
	free(gshade(NULL));
}
