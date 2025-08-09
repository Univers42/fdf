/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:33 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:34:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	marble_color(float t)
{
	uint32_t	dark;
	uint32_t	light;

	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
	dark = 0x404040;
	light = 0xE0E0E0;
	return (blend_colors(dark, light, t));
}

static float	marble_pattern(t_fpoint2 n, const t_texture_system *tex)
{
	float	s;
	float	r;

	s = tex->scale_factor;
	r = sinf(n.x * 10.0f * s
			+ sinf(n.y * 6.0f * s + tex->time_accumulator) * 2.0f)
		* 0.5f + 0.5f;
	return (r);
}

static void	marble_row(t_app *fdf, int y)
{
	const t_texture_system	*t;
	int						x;
	t_fpoint2				n;
	float					p;

	t = gtexture(NULL);
	x = 0;
	while (x < fdf->width)
	{
		n.x = (float)x / (float)fdf->width;
		n.y = (float)y / (float)fdf->height;
		p = marble_pattern(n, t);
		fdf->color[y * fdf->width + x] = blend_colors(
				t->original_colors[y * fdf->width + x],
				marble_color(p),
				0.75f);
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
