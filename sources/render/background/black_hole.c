/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   black_hole.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <wchar.h>

t_black_hole	*gblackhole(void)
{
	static t_black_hole	bh;

	return (&bh);
}

void	black_hole_free(void)
{
	t_black_hole	*bh;

	bh = gblackhole();
	free(bh->lut);
	free(bh->stars);
	bh->lut = NULL;
	bh->stars = NULL;
	bh->init = false;
}

static inline uint32_t	bh_sample(t_black_hole *bh, uint32_t v, int drift)
{
	int	sx;

	if ((v >> 16) == 0xFFFF)
		return (bh->palette[v & 0xFF]);
	sx = (int)(v & 0xFFFF) + drift;
	if (sx >= WIN_WIDTH)
		sx -= WIN_WIDTH;
	return (bh->stars[(v >> 16) * WIN_WIDTH + sx]);
}

/*
 * Per frame: one LUT indirection per pixel; the starfield drifts behind
 * the lens (parallax) by offsetting the source column, so the LUT never
 * needs rebuilding while animating.
 */
void	apply_black_hole_bg(uint32_t *buffer)
{
	t_black_hole	*bh;
	int				drift;
	int				i;

	bh = gblackhole();
	if (!bh->init && !bh->failed)
		black_hole_build(bh);
	if (bh->failed)
		return ((void)wmemset((wchar_t *)buffer, 0,
				(size_t)WIN_WIDTH * WIN_HEIGHT));
	drift = (int)(gdynbg(NULL)->time_accumulator * BH_DRIFT_SPEED)
		% WIN_WIDTH;
	i = -1;
	while (++i < WIN_WIDTH * WIN_HEIGHT)
		buffer[i] = bh_sample(bh, bh->lut[i], drift);
}

/*
 * Real lens interaction: the object is treated as sitting behind the
 * hole, so each vertex at true angular radius b appears at the primary
 * image position th = (b + sqrt(b^2 + 4*Re^2)) / 2 (point-lens
 * equation). Far vertices are barely moved; vertices crossing the
 * center smear onto the Einstein ring, so the hole visibly grabs and
 * wraps the wireframe around itself. Aspect-corrected so the ring the
 * object hugs matches the circular ring in the background LUT.
 */
void	black_hole_warp_points(t_app *f)
{
	t_dynamic_bg_system	*db;
	t_fpoint4			*p;
	float				re2;
	float				xa;
	float				g;

	db = gdynbg(NULL);
	if (!db->active || db->current_bg != DYNAMIC_BG_BLACK_HOLE
		|| !gblackhole()->init || gcam()->active)
		return ;
	re2 = 2.0f * gblackhole()->einstein_r / gviewport()->h;
	re2 = re2 * re2;
	p = f->transformed_points + (f->width * f->height);
	while (--p >= f->transformed_points)
	{
		xa = p->x * ((float)gviewport()->w / gviewport()->h);
		g = xa * xa + p->y * p->y;
		if (g < 1e-12f)
			g = 1e-12f;
		g = 0.5f + 0.5f * sqrtf(1.0f + 4.0f * re2 / g);
		p->x *= g;
		p->y *= g;
	}
}
