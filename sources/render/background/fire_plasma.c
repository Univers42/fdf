/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_plasma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:57:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	fire_gradient(float v)
{
	if (v < 0.2f)
		return (lerp_color(0x000000, 0x330000, v * 5.0f));
	if (v < 0.4f)
		return (lerp_color(0x330000, 0xFF0000, (v - 0.2f) * 5.0f));
	if (v < 0.6f)
		return (lerp_color(0xFF0000, 0xFF4400, (v - 0.4f) * 5.0f));
	if (v < 0.8f)
		return (lerp_color(0xFF4400, 0xFFFF00, (v - 0.6f) * 5.0f));
	return (lerp_color(0xFFFF00, 0xFFFFFF, (v - 0.8f) * 5.0f));
}

static uint32_t	fire_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	float		base;
	t_fpoint3	r;
	float		intensity;

	n.x = (float)x / WIN_WIDTH;
	n.y = (float)y / WIN_HEIGHT;
	base = 1.0f - n.y;
	r.x = sinf((n.x * 8.0f + t * 4.0f) * M_PI);
	r.y = sinf((n.x * 15.0f + t * 6.0f) * M_PI);
	r.y = sinf((n.y * 12.0f + t * 5.0f) * M_PI);
	intensity = base * (0.7f + 0.3f * (r.x + r.y + r.y) / 3.0f);
	if (intensity < 0.0f)
		intensity = 0.0f;
	if (intensity > 1.0f)
		intensity = 1.0f;
	return (fire_gradient(intensity));
}

void	apply_fire_plasma_bg(uint32_t *b)
{
	int		y;
	int		x;
	float	t;

	t = gdynbg(NULL)->time_accumulator;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			b[y * WIN_WIDTH + x] = fire_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
