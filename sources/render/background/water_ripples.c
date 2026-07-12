/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   water_ripples.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:10:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	get_ripple_centers(t_fpoint2 *c, float t)
{
	c[0].x = 0.3f + 0.2f * sinf(t * 0.8f);
	c[0].y = 0.4f + 0.2f * cosf(t * 0.6f);
	c[1].x = 0.7f + 0.15f * sinf(t * 1.2f);
	c[1].y = 0.6f + 0.15f * cosf(t * 0.9f);
	c[2].x = 0.5f + 0.1f * sinf(t * 1.5f);
	c[2].y = 0.3f + 0.1f * cosf(t * 1.1f);
}

static float	ripple_wave(t_fpoint2 n, t_fpoint2 c, t_fpoint3 p, float t)
{
	float	d;

	d = sqrtf((n.x - c.x) * (n.x - c.x) + (n.y - c.y) * (n.y - c.y));
	return (sinf((d * p.x - t * p.y) * M_PI) * expf(-d * p.z));
}

static float	ripple_sum(t_fpoint2 n, t_fpoint2 *c, float t)
{
	t_fpoint3	p;
	float		h;

	p.x = 30.0f;
	p.y = 8.0f;
	p.z = 3.0f;
	h = ripple_wave(n, c[0], p, t);
	p.x = 25.0f;
	p.y = 6.0f;
	p.z = 4.0f;
	h += ripple_wave(n, c[1], p, t);
	p.x = 35.0f;
	p.y = 10.0f;
	p.z = 5.0f;
	h += ripple_wave(n, c[2], p, t);
	return (h);
}

static uint32_t	water_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	t_fpoint2	c[3];
	float		h;

	n.x = (float)x / BG_W;
	n.y = (float)y / BG_H;
	get_ripple_centers(c, t);
	h = ripple_sum(n, c, t);
	h = h * 0.5f + 0.5f;
	if (h > 0.8f)
		return (lerp_color(0x4488BB, 0xAADDFF, (h - 0.8f) * 5.0f));
	return (lerp_color(0x001133, 0x4488BB, h));
}

void	apply_water_ripples_bg(uint32_t *b)
{
	int		y;
	int		x;
	float	t;

	t = gdynbg(NULL)->time_accumulator;
	y = 0;
	while (y < BG_H)
	{
		x = 0;
		while (x < BG_W)
		{
			b[y * BG_W + x] = water_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
