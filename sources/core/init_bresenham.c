/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bresenham.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:46:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/09/01 08:34:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * @brief Initializes the Bresenham state for line drawing between
 two transformed points.
 *
 * This function sets up the necessary data for the Bresenham line algorithm,
 * including screen coordinates, colors, and deltas. The transformed points
 * are in normalized device coordinates (NDC) [-1,1], which are mapped to screen
 * pixel coordinates [0, WIN_WIDTH] and [0, WIN_HEIGHT].
 *
 * @param b Pointer to the Bresenham state structure to initialize.
 * @param fdf Pointer to the main application structure.
 * @param i Index of the edge in the edges array.
 */
void	bresenham_init(
	t_bresenham_state *b, t_app *fdf, int i
) {
	t_fpoint4	*p1;
	t_fpoint4	*p2;

	p1 = &fdf->transformed_points[fdf->edges[i][0]];
	p2 = &fdf->transformed_points[fdf->edges[i][1]];
	b->color1 = fdf->color[fdf->edges[i][0]];
	b->color2 = fdf->color[fdf->edges[i][1]];
	b->p1[0] = ndc_to_screen_x(p1->x);
	b->p1[1] = ndc_to_screen_y(p1->y);
	b->p1[2] = ndc_to_depth(p1->z);
	b->p2[0] = ndc_to_screen_x(p2->x);
	b->p2[1] = ndc_to_screen_y(p2->y);
	b->p2[2] = ndc_to_depth(p2->z);
	init_deltas(b);
}

/**
 * @brief Initializes Bresenham deltas and color interpolation values.
 *
 * Computes the absolute deltas for each axis and sets up
 the step direction
 * and color channel differences for interpolation.
 *
 * @param b Pointer to the Bresenham state struct.
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

/**
 * @brief Normalizes color deltas by the maximum delta for interpolation.
 *
 * Divides color deltas by the larger of delta X or Y to prepare
 for per-step interpolation.
 *
 * @param b Pointer to the Bresenham state structure.
 */
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
