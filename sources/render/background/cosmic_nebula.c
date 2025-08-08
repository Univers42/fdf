/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosmic_nebula.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:49:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:50:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	nebula_mix(float d)
{
	if (d > 0.8f)
		return (lerp_color(0x8000FF, 0xFFFFFF, (d - 0.8f) * 5.0f));
	if (d > 0.6f)
		return (lerp_color(0xFF0080, 0x8000FF, (d - 0.6f) * 5.0f));
	if (d > 0.3f)
		return (lerp_color(0x200040, 0xFF0080, (d - 0.3f) * 3.33f));
	if (d > 0.1f)
		return (lerp_color(0x000000, 0x200040, (d - 0.1f) * 5.0f));
	return (0x000000);
}

static uint32_t	nebula_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	float		n1;
	float		n2;
	float		n3;
	float		d;

	n.x = (float)x / WIN_WIDTH;
	n.y = (float)y / WIN_HEIGHT;
	n1 = sinf((n.x * 4.0f + t * 0.3f) * M_PI)
		* cosf((n.y * 3.0f + t * 0.2f) * M_PI);
	n2 = sinf((n.x * 8.0f + t * 0.5f) * M_PI)
		* cosf((n.y * 6.0f + t * 0.4f) * M_PI);
	n3 = sinf((n.x * 12.0f + t * 0.8f) * M_PI)
		* cosf((n.y * 10.0f + t * 0.6f) * M_PI);
	d = (n1 * 0.5f + n2 * 0.3f + n3 * 0.2f + 1.0f) / 2.0f;
	d *= 1.0f - sqrtf(powf(n.x - 0.5f, 2.0f) + powf(n.y - 0.5f, 2.0f));
	return (nebula_mix(d));
}

void	apply_cosmic_nebula_bg(uint32_t *b)
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
			b[y * WIN_WIDTH + x] = nebula_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
