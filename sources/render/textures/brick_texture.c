/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brick_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:21:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdint.h>

static uint32_t	select_brick_color(int row, int col)
{
	int			id;

	id = (row * 1000 + col) % 3;
	if (id == 0)
		return (0xB22222);
	if (id == 1)
		return (0xA0522D);
	return (0x8B4513);
}

static int	is_mortar(float lx, float ly, float bw, float bh)
{
	if (lx < 1.0f || lx > bw - 1.0f)
		return (1);
	if (ly < 1.0f || ly > bh - 1.0f)
		return (1);
	return (0);
}

static void	brick_row(t_app *fdf, float bw, float bh, int y)
{
	int			x;
	int			index;
	t_bound		dim;
	t_fpoint2	l;
	uint32_t	c;

	dim.y = (int)(y / bh);
	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		dim.x = (int)((x + (dim.y % 2) * bw / 2.0f) / bw);
		l.x = fmodf(x + (dim.y % 2) * bw / 2.0f, bw);
		l.y = fmodf(y, bh);
		if (is_mortar(l.x, l.y, bw, bh))
			c = 0xD3D3D3;
		else
			c = select_brick_color(dim.y, dim.x);
		fdf->color[index] = blend_colors(g_texture.original_colors[index],
				c, 0.7f);
		++x;
	}
}

void	apply_brick_texture(t_app *fdf)
{
	int		y;
	float	bw;
	float	bh;

	bw = 12.0f / g_texture.scale_factor;
	bh = 6.0f / g_texture.scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		brick_row(fdf, bw, bh, y);
		++y;
	}
}
