/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:01:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 02:02:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theme.h"
#include "fdf.h"
#include <math.h>

// Per-pixel helpers (non-conflicting)
uint32_t	color_apply_depth_shadow(uint32_t color, float depth_norm)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	float	f;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	f = 1.0f - (0.55f * depth_norm);
	r = (uint8_t)(r * f);
	g = (uint8_t)(g * f);
	b = (uint8_t)(b * f);
	return (pack_rgba(r, g, b, 255));
}

uint32_t	color_apply_ambient_shadow(uint32_t color, float intensity)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	float	f;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	f = 1.0f - (0.35f * intensity);
	r = (uint8_t)(r * f);
	g = (uint8_t)(g * f);
	b = (uint8_t)(b * f);
	return (pack_rgba(r, g, b, 255));
}

/*
 * API functions expected by existing code (void signatures in fdf.h).
 * Simple pass applying uniform factors (stub logic).
 */
void	apply_depth_shadow(t_app *fdf)
{
	int		total;
	int		i;
	float	depth_norm;

	if (!fdf || !fdf->color)
		return ;
	total = fdf->width * fdf->height;
	if (total <= 0)
		return ;
	i = -1;
	while (++i < total)
	{
		depth_norm = (float)(i / fdf->width) / (float)(fdf->height - 1
				+ (fdf->height == 1));
		fdf->color[i] = color_apply_depth_shadow(fdf->color[i], depth_norm);
	}
}

void	apply_ambient_shadows(t_app *fdf)
{
	int		total;
	int		i;
	float	intensity;
	int		y;
	float	ny;

	if (!fdf || !fdf->color)
		return ;
	total = fdf->width * fdf->height;
	if (total <= 0)
		return ;
	i = -1;
	while (++i < total)
	{
		y = i / fdf->width;
		ny = (float)y / (float)(fdf->height - 1 + (fdf->height == 1));
		intensity = 0.5f * (1.0f - (2.0f * fabsf(ny - 0.5f)));
		fdf->color[i] = color_apply_ambient_shadow(fdf->color[i], intensity);
	}
}
