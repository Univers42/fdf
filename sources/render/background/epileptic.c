/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epileptic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:53:51 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	flash_palette(float v)
{
	static const uint32_t	c[] = {
		0x000000, 0xFFFFFF, 0xFF0000, 0x00FF00,
		0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF
	};
	int						i;

	if (v < 0)
		v = 0;
	if (v > 1)
		v = 1;
	i = (int)(v * 7.0f);
	if (i > 7)
		i = 7;
	return (c[i]);
}

static uint32_t	epileptic_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	float		p1;
	float		p2;
	float		p3;
	float		val;

	n.x = (float)x / WIN_WIDTH;
	n.y = (float)y / WIN_HEIGHT;
	p1 = sinf((n.x * 10.0f + t * 25.0f) * M_PI);
	p2 = cosf((n.y * 8.0f + t * 30.0f) * M_PI);
	p3 = sinf(((n.x + n.y) * 15.0f + t * 40.0f) * M_PI);
	val = (p1 + p2 + p3 + sinf(t * 20.0f)) / 4.0f;
	val = (val + 1.0f) / 2.0f;
	return (flash_palette(val));
}

void	apply_epileptic_flash_bg(uint32_t *b)
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
			b[y * WIN_WIDTH + x] = epileptic_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
