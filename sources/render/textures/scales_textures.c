/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scales_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:37:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:37:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	scale_color(float h)
{
	return (blend_colors(0x2F4F4F, 0x87CEEB, h));
}

static uint32_t	scale_pixel(int x, int y, float sz, t_app *fdf)
{
	t_fpoint2	n;
	t_fpoint2	s;
	t_fpoint2	l;
	float		dist;
	float		hl;

	n.x = (float)x / fdf->width;
	n.y = (float)y / fdf->height;
	s.x = x / sz;
	s.y = y / sz;
	if (((int)s.y % 2) == 1)
		s.x += 0.5f;
	l.x = s.x - floorf(s.x) - 0.5f;
	l.y = s.y - floorf(s.y) - 0.5f;
	dist = sqrtf(l.x * l.x + l.y * l.y);
	hl = 1.0f - dist * 2.0f;
	if (hl < 0.0f)
		hl = 0.0f;
	hl += sinf((n.x * 10.0f + n.y * 8.0f
				+ g_texture.time_accumulator * 3.0f) * M_PI) * 0.2f;
	return (scale_color(hl));
}

static void	scale_row(t_app *fdf, float sz, int y)
{
	int			x;
	int			index;
	uint32_t	tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		tc = scale_pixel(x, y, sz, fdf);
		fdf->color[index] = blend_colors(g_texture.original_colors[index],
				tc, 0.7f);
		++x;
	}
}

void	apply_scales_texture(t_app *fdf)
{
	int		y;
	float	scale_size;

	scale_size = 8.0f / g_texture.scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		scale_row(fdf, scale_size, y);
		++y;
	}
}
