/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:52:17 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_x_major(t_bresenham_state *b, unsigned int *screen)
{
	draw_line_bresenham(b, screen, 0);
}

void	draw_line_y_major(t_bresenham_state *b, unsigned int *screen)
{
	draw_line_bresenham(b, screen, 1);
}

static inline bool	line_in_bounds(const t_bresenham_state *b)
{
	return ((unsigned int)b->p1[0] < WIN_WIDTH
		&& (unsigned int)b->p1[1] < WIN_HEIGHT
		&& (unsigned int)b->p2[0] < WIN_WIDTH
		&& (unsigned int)b->p2[1] < WIN_HEIGHT);
}

void	draw_line_bresenham(t_bresenham_state *b,
			unsigned int *screen, int major_axis)
{
	t_bresenham_ctx	ctx;

	init_color_delta(b);
	b->error_count = 2 * b->delta[1 - major_axis] - b->delta[major_axis];
	ctx.bresenham = b;
	ctx.screen = screen;
	ctx.coord[0] = b->p1[0];
	ctx.coord[1] = b->p1[1];
	ctx.limit = b->delta[major_axis];
	ctx.major_axis = major_axis;
	if (line_in_bounds(b))
	{
		if (b->color1 == b->color2)
			line_fast_solid(&ctx);
		else
			line_fast(&ctx);
	}
	else
		line_guarded(&ctx);
}
