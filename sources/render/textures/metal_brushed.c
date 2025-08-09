/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal_brushed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:33 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:47:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	metal_color(float intensity)
{
	uint32_t	dark;
	uint32_t	bright;

	dark = 0x404040;
	bright = 0xC0C0C0;
	return (blend_colors(dark, bright, intensity));
}

static void	metal_row(t_app *fdf, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	int						x;
	int						index;
	t_fpoint2				n;
	t_retouch				m;
	uint32_t				tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		n.x = (float)x / fdf->width;
		n.y = (float)y / fdf->height;
		m.lines = sinf(n.y * 80.0f * t->scale_factor) * 0.3f;
		m.highlight = sinf((n.x + t->time_accumulator * 0.8f) * M_PI * 4.0f) * 0.2f;
		m.intensity = 0.5f + m.lines + m.highlight;
		if (m.intensity < 0.0f)
			m.intensity = 0.0f;
		if (m.intensity > 1.0f)
			m.intensity = 1.0f;
		tc = metal_color(m.intensity);
		fdf->color[index] = blend_colors(t->original_colors[index], tc, 0.8f);
		++x;
	}
}

void	apply_metal_brushed_texture(t_app *fdf)
{
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		metal_row(fdf, y);
		++y;
	}
}
