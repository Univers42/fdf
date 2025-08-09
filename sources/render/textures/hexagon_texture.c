/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexagon_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:48:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	hexagon_color(float dist)
{
	if (dist < 0.1f)
		return (0xFFD700);
	if (dist > 0.4f)
		return (0x000000);
	return (0xFFA500);
}

static uint32_t	hexagon_pixel(int x, int y, float hex_size)
{
	float	hex_x;
	float	hex_y;
	float	local_x;
	float	local_y;
	float	dist;

	hex_x = x / hex_size;
	hex_y = y / hex_size;
	local_x = hex_x - floorf(hex_x) - 0.5f;
	local_y = hex_y - floorf(hex_y) - 0.5f;
	dist = fmaxf(fabsf(local_x), fabsf(local_y) * 0.866f);
	return (hexagon_color(dist));
}

static void	hexagon_row(t_app *fdf, float hex_size, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	int						x;
	int						index;
	uint32_t				tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		tc = hexagon_pixel(x, y, hex_size);
		fdf->color[index] = blend_colors(t->original_colors[index], tc, 0.6f);
		++x;
	}
}

void	apply_hexagon_texture(t_app *fdf)
{
	const t_texture_system	*t = gtexture(NULL);
	int						y;
	float					hex_size;

	hex_size = 10.0f / t->scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		hexagon_row(fdf, hex_size, y);
		++y;
	}
}
