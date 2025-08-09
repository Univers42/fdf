/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow_vortex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:06:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	rainbow_sample(float t)
{
	static const uint32_t	c[] = {
		0xFF0000, 0xFF8000, 0xFFFF00, 0x00FF00,
		0x00FFFF, 0x0000FF, 0x8000FF, 0xFF0000
	};
	int						i;
	float					local;

	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	t *= 7.0f;
	i = (int)t;
	if (i >= 7)
		i = 6;
	local = t - (float)i;
	return (lerp_color(c[i], c[i + 1], local));
}

static uint32_t	vortex_pixel(int x, int y, float time)
{
	t_fpoint2	n;
	t_fpoint3	a;
	uint32_t	col;
	float		fade;

	n.x = (float)x / WIN_WIDTH - 0.5f;
	n.y = (float)y / WIN_HEIGHT - 0.5f;
	a.x = sqrtf(n.x * n.x + n.y * n.y);
	a.y = atan2f(n.y, n.x);
	a.z = fmodf((a.y + a.x * 8.0f - time * 4.0f)
			/ (2.0f * M_PI) + 1.0f, 1.0f);
	col = rainbow_sample(a.z);
	fade = 1.0f - a.x;
	if (fade < 0.0f)
		fade = 0.0f;
	return (((uint8_t)(((col >> 16) & 0xFF) * fade) << 16)
		| ((uint8_t)(((col >> 8) & 0xFF) * fade) << 8)
		| ((uint8_t)((col & 0xFF) * fade)));
}

void	apply_rainbow_vortex_bg(uint32_t *buf)
{
	int		y;
	int		x;
	float	time;

	time = gdynbg(NULL)->time_accumulator;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			buf[y * WIN_WIDTH + x] = vortex_pixel(x, y, time);
			++x;
		}
		++y;
	}
}
