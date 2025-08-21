/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bresenham.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:46:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 15:14:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	bresenham_init(
	t_bresenham_state *b, t_app *fdf, int i
) {
	t_fpoint4	*p1;
	t_fpoint4	*p2;

	p1 = &fdf->transformed_points[fdf->edges[i][0]];
	p2 = &fdf->transformed_points[fdf->edges[i][1]];
	b->color1 = fdf->color[fdf->edges[i][0]];
	b->color2 = fdf->color[fdf->edges[i][1]];
	b->p1[0] = (int)((p1->x + 1) / 2 * WIN_WIDTH);
	b->p1[1] = (int)((1 - p1->y) / 2 * WIN_HEIGHT);
	b->p1[2] = (int)fminf(fmaxf(((p1->z + 1) / 2.0f * 255.0f) + 50, 150), 255);
	b->p2[0] = (int)((p2->x + 1) / 2 * WIN_WIDTH);
	b->p2[1] = (int)((1 - p2->y) / 2 * WIN_HEIGHT);
	b->p2[2] = (int)fminf(fmaxf(((p2->z + 1) / 2.0f * 255.0f) + 50, 150), 255);
	init_deltas(b);
}

/**
 * init_deltas - Initializes Bresenham deltas and color interpolation values.
 * @b: Pointer to the Bresenham state struct.
 *
 * Computes the absolute deltas for each axis and sets up the step direction
 * and color channel differences for interpolation.
 *
 * Example:
 *   init_deltas(&bresenham);
 */
void	init_deltas(t_bresenham_state *b)
{
	b->delta[0] = b->p2[0] - b->p1[0];
	b->delta[1] = b->p2[1] - b->p1[1];
	b->delta[2] = b->p2[2] - b->p1[2];
	b->step[0] = 1;
	b->step[1] = 1;
	if (b->delta[0] < 0)
		b->step[0] = -1;
	if (b->delta[1] < 0)
		b->step[1] = -1;
	b->delta[0] = ft_abs(b->p2[0] - b->p1[0]);
	b->delta[1] = ft_abs(b->p2[1] - b->p1[1]);
	b->delta[2] = ft_abs(b->p2[2] - b->p1[2]);
	b->color_r_delta = (int)(b->color2 >> 16 & 0xff)
		- (int)(b->color1 >> 16 & 0xff);
	b->color_g_delta = (int)(b->color2 >> 8 & 0xff)
		- (int)(b->color1 >> 8 & 0xff);
	b->color_b_delta = (int)(b->color2 & 0xff) - (int)(b->color1 & 0xff);
}

void	init_color_delta(t_bresenham_state *b)
{
	float	delta;

	delta = b->delta[1];
	if (b->delta[0] >= b->delta[1])
		delta = b->delta[0];
	if (delta == 0)
		delta = 1.0f;
	b->color_r_delta /= delta;
	b->color_g_delta /= delta;
	b->color_b_delta /= delta;
}
