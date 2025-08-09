/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liquid_metal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:05:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	metal_lerp(float v)
{
	if (v > 0.85f)
		return (0xFFFFFF);
	if (v > 0.6f)
		return (lerp_color(0xCCCCCC, 0xFFFFFF, (v - 0.6f) * 4.0f));
	if (v > 0.3f)
		return (lerp_color(0x888888, 0xCCCCCC, (v - 0.3f) * 3.33f));
	return (lerp_color(0x333333, 0x888888, v * 3.33f));
}

static uint32_t	metal_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	float		f1;
	float		f2;
	float		f3;
	float		r;

	n.x = (float)x / WIN_WIDTH;
	n.y = (float)y / WIN_HEIGHT;
	f1 = sinf((n.x * 6.0f + n.y * 2.0f + t * 2.0f) * M_PI);
	f2 = sinf((n.x * 8.0f - n.y * 3.0f + t * 1.5f) * M_PI);
	f3 = sinf((n.x * 4.0f + n.y * 4.0f + t * 3.0f) * M_PI);
	r = (f1 + f2 + f3) / 3.0f;
	r = (r + 1.0f) / 2.0f;
	return (metal_lerp(r));
}

void	apply_liquid_metal_bg(uint32_t *b)
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
			b[y * WIN_WIDTH + x] = metal_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
