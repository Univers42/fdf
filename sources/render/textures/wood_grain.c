/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wood_grain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:41:50 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	wood_color(float intensity)
{
	uint32_t	light;
	uint32_t	dark;

	light = 0xDEB887;
	dark = 0x8B4513;
	return (blend_colors(light, dark, intensity));
}

static uint32_t	wood_pixel(int x, int y, t_app *fdf)
{
	const t_texture_system	*t = gtexture(NULL);
	t_fpoint2				n;
	t_fpoint3				g;
	float					in;

	n.x = (float)x / fdf->width;
	n.y = (float)y / fdf->height;
	g.x = sinf((n.x * 20.0f + t->time_accumulator * 0.5f) * M_PI);
	g.y = sinf((n.y * 8.0f + n.x * 2.0f) * M_PI);
	g.z = sinf((n.x * 40.0f + g.x * 5.0f) * M_PI);
	in = (g.x + g.y + g.z) / 3.0f;
	in = (in + 1.0f) / 2.0f;
	return (wood_color(in));
}

static void	wood_row(t_app *fdf, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	int						x;
	int						index;
	uint32_t				tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		tc = wood_pixel(x, y, fdf);
		fdf->color[index] = blend_colors(t->original_colors[index], tc, 0.7f);
		++x;
	}
}

void	apply_wood_grain_texture(t_app *fdf)
{
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		wood_row(fdf, y);
		++y;
	}
}
