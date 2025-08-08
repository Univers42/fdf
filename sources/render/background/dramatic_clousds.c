/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dramatic_clousds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:50:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:51:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	cloud_color(float d, float flash)
{
	uint32_t	base;

	base = lerp_color(0x202030, 0x808090, d);
	if (flash > 0.98f && d > 0.7f)
		return (0xFFFFBB);
	return (base);
}

static uint32_t	cloud_pixel(int x, int y, float t)
{
	t_fpoint2	n;
	float		c1;
	float		c2;
	float		c3;
	float		d;

	n.x = (float)x / WIN_WIDTH;
	n.y = (float)y / WIN_HEIGHT;
	c1 = sinf((n.x * 8.0f + t * 0.5f) * M_PI)
		* cosf((n.y * 6.0f + t * 0.3f) * M_PI);
	c2 = sinf((n.x * 15.0f + t * 0.8f) * M_PI)
		* cosf((n.y * 12.0f + t * 0.6f) * M_PI);
	c3 = sinf(((n.x + n.y) * 20.0f + t * 1.2f) * M_PI);
	d = (c1 * 0.5f + c2 * 0.3f + c3 * 0.2f + 1.0f) / 2.0f;
	return (cloud_color(d, sinf(t * 15.0f + n.x * 50.0f)));
}

void	apply_dramatic_clouds_bg(uint32_t *b)
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
			b[y * WIN_WIDTH + x] = cloud_pixel(x, y, t);
			++x;
		}
		++y;
	}
}
