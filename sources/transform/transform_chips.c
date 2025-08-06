/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_chips.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 20:25:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_math.h"
#include <math.h>

/**
 * controls the curvature
 * Normalize coordonate to -1;1
 * Hyperbolic parabaloid equation : z = a * (x² - y²)
 * This creates the classic saddle shape
 * Add the original z variation for texture
 * Apply transformation matrix
 */
void	apply_chips_transformation(t_app *fdf)
{
	t_point3	norm;
	t_point3	chip;
	float	scale;
	float	a;
	int		y;
	int		x;
	int		index;
	float	sp[4];
	float	*dp;

	scale = fminf(fdf->width, fdf->height) / 3.0f;
	a = 0.3f;
	y = -1;
	while (++y < fdf->height)
	{
		x = -1;
		while (++x < fdf->width)
		{
			index = y * fdf->width + x;
			norm.x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			norm.y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			chip.x = norm.x * scale;
			chip.y = norm.y * scale;
			chip.z = a * (norm.x * norm.x - norm.y * norm.y) * scale;
			chip.z += fdf->points[index] * 0.1f;
			sp[0] = chip.x;
			sp[1] = chip.y;
			sp[2] = chip.z;
			sp[3] = 1;
			dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
