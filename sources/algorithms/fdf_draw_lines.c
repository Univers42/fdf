/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:52:25 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * When the projected grid spacing falls below one pixel (maps wider than
 * the viewport), neighbouring lines land on the same pixels: pure
 * overdraw. Walk the grid with a stride that keeps spacing ~1px; the
 * image is visually identical and the edge count drops by stride^2.
 * ponytail: one isotropic stride from the map center; per-axis strides
 * if anisotropic projections ever need it.
 */
int	fdf_grid_stride(t_app *f)
{
	t_fpoint4	*a;
	float		dx;
	float		dy;
	float		s;

	if (f->width < 2 || f->height < 2 || transition_is_active())
		return (1);
	a = &f->transformed_points[(f->height / 2) * f->width + f->width / 2 - 1];
	dx = (a[1].x - a->x) * (gviewport()->w * 0.5f);
	dy = (a[1].y - a->y) * (gviewport()->h * 0.5f);
	s = fabsf(dx);
	if (fabsf(dy) > s)
		s = fabsf(dy);
	if (s >= 1.0f || s <= 0.0f)
		return (1);
	if (s < 0.01f)
		return (100);
	return ((int)(1.0f / s));
}

/*
 * Camera-mode LOD: projected spacing varies with distance, so the
 * stride is recomputed per row from that row's center cell. Near rows
 * keep full detail, far rows decimate: a distance-adaptive LOD.
 */
/*
 * axis 0: stride along a row (column step); axis 1: stride across rows.
 * They differ hugely under perspective: near the horizon hundreds of
 * rows foreshorten onto a few screen lines, so the row stride explodes
 * there and kills the overdraw, while in-row detail stays fine.
 */
int	fdf_row_stride(t_app *f, int y, float target, int axis)
{
	t_fpoint4	a;
	t_fpoint4	b;
	float		s;
	float		sy;

	if (!gcam()->active)
		return (fdf_grid_stride(f));
	if (f->width < 3 || y + 1 >= f->height)
		return (1);
	a = f->transformed_points[y * f->width + f->width / 2];
	if (axis == 0)
		b = f->transformed_points[y * f->width + f->width / 2 + 1];
	else
		b = f->transformed_points[(y + 1) * f->width + f->width / 2];
	if (a.w < CAM_NEAR || b.w < CAM_NEAR)
		return (1);
	s = fabsf(b.x / b.w - a.x / a.w) * (gviewport()->w * 0.5f);
	sy = fabsf(b.y / b.w - a.y / a.w) * (gviewport()->h * 0.5f);
	if (sy > s)
		s = sy;
	if (s >= target || s <= 0.0f)
		return (1);
	if (s < 0.01f * target)
		return (100);
	return ((int)(target / s + 0.5f));
}

static inline int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
 * The wireframe topology is the grid itself: right and down neighbours
 * of every (strided) vertex. No edge array needed.
 */
void	fdf_draw_lines(t_app *f)
{
	int	k;
	int	ky;
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < f->height)
	{
		k = fdf_row_stride(f, y, 1.0f, 0);
		ky = fdf_row_stride(f, y, 1.0f, 1);
		x = 0;
		while (x < f->width)
		{
			i = y * f->width + x;
			if (x < f->width - 1)
				draw_edge(f, i, y * f->width + imin(x + k, f->width - 1));
			if (y < f->height - 1)
				draw_edge(f, i, imin(y + ky, f->height - 1) * f->width + x);
			x += k;
		}
		y += ky;
	}
}
