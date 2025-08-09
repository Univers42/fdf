/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scales_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:37:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:48:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	scale_color(float h)
{
	return (blend_colors(0x2F4F4F, 0x87CEEB, h));
}

static float	scale_highlight(t_point2 c, t_app *fdf,
	const t_texture_system *t)
{
	t_fpoint2	n;
	float		hl;

	n.x = (float)c.x / (float)fdf->width;
	n.y = (float)c.y / (float)fdf->height;
	hl = sinf((n.x * 10.0f + n.y * 8.0f
				+ t->time_accumulator * 3.0f) * M_PI) * 0.2f;
	return (hl);
}

static uint32_t	scale_pixel(t_app *fdf, const t_texture_system *t,
	t_point2 c, float sz)
{
	t_fpoint2	s;
	t_fpoint2	l;
	float		hl;

	s.x = (float)c.x / sz;
	s.y = (float)c.y / sz;
	if (((int)s.y % 2) == 1)
		s.x += 0.5f;
	l.x = s.x - floorf(s.x) - 0.5f;
	l.y = s.y - floorf(s.y) - 0.5f;
	hl = 1.0f - sqrtf(l.x * l.x + l.y * l.y) * 2.0f;
	if (hl < 0.0f)
		hl = 0.0f;
	hl += scale_highlight(c, fdf, t);
	return (scale_color(hl));
}

static void	scale_row(t_app *fdf, float sz, int y)
{
	const t_texture_system	*t;
	t_point2				c;

	t = gtexture(NULL);
	c.y = y;
	c.x = 0;
	while (c.x < fdf->width)
	{
		fdf->color[c.y * fdf->width + c.x] = blend_colors(
				t->original_colors[c.y * fdf->width + c.x],
				scale_pixel(fdf, t, c, sz),
				0.7f);
		++c.x;
	}
}

void	apply_scales_texture(t_app *fdf)
{
	const t_texture_system	*t = gtexture(NULL);
	int						y;
	float					scale_size;

	scale_size = 8.0f / t->scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		scale_row(fdf, scale_size, y);
		++y;
	}
}
