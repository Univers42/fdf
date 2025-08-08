/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vibrant_grad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:58:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 21:01:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	rainbow_band(float t)
{
	static const uint32_t	c[] = {
		0xFF0000, 0xFF8000, 0xFFFF00, 0x00FF00,
		0x00FFFF, 0x0000FF, 0x8000FF, 0xFF00FF
	};
	int						i;
	float					loc;

	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	t *= 7.0f;
	i = (int)t;
	if (i >= 7)
		i = 6;
	loc = t - (float)i;
	return (lerp_color(c[i], c[i + 1], loc));
}

static uint32_t	vibrant_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	float		w1;
	float		w2;
	float		w3;
	float		f;

	n.x = (float)x / WIN_WIDTH;
	n.y = (float)y / WIN_HEIGHT;
	w1 = sinf((n.x * 4.0f + t * 2.0f) * M_PI);
	w2 = sinf((n.y * 3.0f + t * 1.5f) * M_PI);
	w3 = sinf(((n.x + n.y) * 2.0f + t * 3.0f) * M_PI);
	f = (w1 + w2 + w3) / 3.0f;
	f = (f + 1.0f) / 2.0f;
	return (rainbow_band(f));
}

void	apply_vibrant_gradient_bg(uint32_t *b)
{
	int		y;
	int		x;
	float	t;

	t = g_dynamic_bg.time_accumulator;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			b[y * WIN_WIDTH + x] = vibrant_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
