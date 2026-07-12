/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:07:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	matrix_clear(uint32_t *b)
{
	int	i;

	i = 0;
	while (i < BG_W * BG_H)
		b[i++] = 0x000000;
}

static void	matrix_segment(uint32_t *b, int col, int tr, float drop)
{
	t_point2	p;
	int			dx;
	float		fade;
	uint32_t	color;

	p.y = (int)(drop - tr * 25);
	if (p.y < 0 || p.y >= BG_H)
		return ;
	fade = 1.0f - tr / 15.0f;
	if (tr == 0)
		color = 0x00FF00;
	else if (tr < 3)
		color = 0x00CC00;
	else if (tr < 8)
		color = (uint32_t)(0x008800 * fade);
	else
		color = (uint32_t)(0x004400 * fade);
	dx = 0;
	while (dx < 15)
	{
		p.x = col * 20 + dx + 2;
		if (p.x >= 0 && p.x < BG_W)
			b[p.y * BG_W + p.x] = color;
		++dx;
	}
}

static void	matrix_column(uint32_t *b, int col, float time)
{
	float	drop;
	int		tr;

	drop = fmodf(time * (8.0f + (col % 3) * 2.0f) + col * 0.7f,
			BG_H + 200.0f) - 100.0f;
	tr = 0;
	while (tr < 15)
	{
		matrix_segment(b, col, tr, drop);
		++tr;
	}
}

void	apply_matrix_rain_bg(uint32_t *b)
{
	int		col;
	int		nc;
	float	time;

	time = gdynbg(NULL)->time_accumulator;
	matrix_clear(b);
	nc = BG_W / 20;
	col = 0;
	while (col < nc)
	{
		matrix_column(b, col, time);
		++col;
	}
}
