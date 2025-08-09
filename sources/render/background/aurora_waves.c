/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aurora_waves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:49:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	aurora_mix(float v)
{
	if (v > 0.7f)
		return (lerp_color(0x00FF44, 0x8844FF, (v - 0.7f) * 3.33f));
	if (v > 0.4f)
		return (lerp_color(0x0044FF, 0x00FF44, (v - 0.4f) * 3.33f));
	if (v > 0.1f)
		return (lerp_color(0x000011, 0x0044FF, (v - 0.1f) * 3.33f));
	return (0x000011);
}

static uint32_t	aurora_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	t_fpoint3	w;
	float		i;

	n.x = (float)x / WIN_WIDTH;
	n.y = (float)y / WIN_HEIGHT;
	w.x = sinf((n.y * 8.0f + n.x * 2.0f + t * 2.0f) * M_PI);
	w.y = sinf((n.y * 12.0f + n.x * 1.5f + t * 1.5f) * M_PI);
	w.z = sinf((n.y * 6.0f + n.x * 3.0f + t * 3.0f) * M_PI);
	i = (w.x + w.y + w.z) / 3.0f;
	i = (i + 1.0f) / 2.0f;
	i *= (1.0f - n.y) * (1.0f - n.y);
	return (aurora_mix(i));
}

void	apply_aurora_waves_bg(uint32_t *b)
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
			b[y * WIN_WIDTH + x] = aurora_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
