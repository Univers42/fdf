/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_storm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:17:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 20:19:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	storm_base(uint32_t *b)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		b[i] = 0x111122;
		++i;
	}
}

void	draw_bolt_core(uint32_t *b, int px, int py)
{
	int	gx;
	int	gy;

	gy = -1;
	while (gy <= 1)
	{
		gx = -1;
		while (gx <= 1)
		{
			if (px + gx >= 0 && px + gx < WIN_WIDTH
				&& py + gy >= 0 && py + gy < WIN_HEIGHT)
				b[(py + gy) * WIN_WIDTH + (px + gx)] = 0xFFFFFF;
			++gx;
		}
		++gy;
	}
}

void	draw_bolt_halo(uint32_t *b, int px, int py)
{
	int	gx;
	int	gy;
	int	dist;

	gy = -5;
	while (gy <= 5)
	{
		gx = -5;
		while (gx <= 5)
		{
			if (px + gx >= 0 && px + gx < WIN_WIDTH
				&& py + gy >= 0 && py + gy < WIN_HEIGHT)
			{
				dist = gx * gx + gy * gy;
				if (dist > 2 && dist <= 25)
					b[(py + gy) * WIN_WIDTH + (px + gx)] = 0xCCCCFF;
			}
			++gx;
		}
		++gy;
	}
}

void	lightning_draw(uint32_t *b, int sx, int ex, float fade)
{
	int			seg;
	t_point2	p;

	seg = 0;
	while (seg < 20)
	{
		p.y = (int)((float)WIN_HEIGHT * seg / 20.0f);
		p.x = sx + (int)((ex - sx) * seg / 20.0f
				+ sinf(seg * 10.0f) * 50.0f);
		draw_bolt_core(b, p.x, p.y);
		draw_bolt_halo(b, p.x, p.y);
		++seg;
	}
	(void)fade;
}

void	storm_bolts(uint32_t *b, float t)
{
	int		i;
	float	bt;

	i = 0;
	while (i < 5)
	{
		bt = fmodf(t * 3.0f + i * 1.7f, 4.0f);
		if (bt < 0.1f)
			lightning_draw(b, (i * 200 + 100) % WIN_WIDTH,
				((i * 200 + 100) % WIN_WIDTH)
				+ (int)(sinf(i * 1.3f) * 200.0f),
				1.0f - (bt / 0.1f));
		++i;
	}
}
