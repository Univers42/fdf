/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:24:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	select_marble_color(float m, uint32_t w, uint32_t g, uint32_t d)
{
	if (m > 0.8f)
		return (w);
	if (m < 0.2f)
		return (d);
	return (g);
}

static uint32_t	calc_marble_pixel(int x, int y, t_app *fdf)
{
	t_fpoint2	n;
	float		v1;
	float		v2;
	float		v3;
	float		m;

	n.x = (float)x / fdf->width;
	n.y = (float)y / fdf->height;
	v1 = sinf((n.x * 6.0f + n.y * 4.0f
				+ g_texture.time_accumulator * 0.3f) * M_PI);
	v2 = sinf((n.x * 8.0f - n.y * 6.0f
				+ g_texture.time_accumulator * 0.2f) * M_PI);
	v3 = sinf((n.x * 12.0f + n.y * 8.0f) * M_PI);
	m = (v1 + v2 + v3) / 3.0f;
	m = (m + 1.0f) / 2.0f;
	return (select_marble_color(m, 0xF8F8FF, 0xC0C0C0, 0x696969));
}

static void	marble_row(t_app *fdf, int y)
{
	int			x;
	int			index;
	uint32_t	tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		tc = calc_marble_pixel(x, y, fdf);
		fdf->color[index] = blend_colors(g_texture.original_colors[index],
				tc, 0.6f);
		++x;
	}
}

void	apply_marble_texture(t_app *fdf)
{
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		marble_row(fdf, y);
		++y;
	}
}
