/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brick_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:45:48 by dlesieur         ###   ########.fr       */
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
	const t_texture_system	*t = gtexture(NULL);
	t_pos_check				pos;
	t_bound					dim;
	t_fpoint2				l;
	uint32_t				c;

	dim.y = (int)(y / bh);
	pos.x = -1;
	while (++pos.x < fdf->width)
	{
		pos.index = y * fdf->width + pos.x;
		dim.x = (int)((pos.x + (dim.y % 2) * bw / 2.0f) / bw);
		l.x = fmodf(pos.x + (dim.y % 2) * bw / 2.0f, bw);
		l.y = fmodf(y, bh);
		if (is_mortar(l.x, l.y, bw, bh))
			c = 0xD3D3D3;
		else
			c = select_brick_color(dim.y, dim.x);
		fdf->color[pos.index] = blend_colors(t->original_colors[pos.index],
				c, 0.7f);
	}
}

void	apply_brick_texture(t_app *fdf)
{
	const t_texture_system	*t = gtexture(NULL);
	int						y;
	float					bw;
	float					bh;

	bw = 12.0f / t->scale_factor;
	bh = 6.0f / t->scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		brick_row(fdf, bw, bh, y);
		++y;
	}
}
