/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fold_effect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 22:59:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_fold_to_points(t_app *fdf)
{
	int		y;
	int		x;
	int		index;
	float	fold_effect;
	float	fold_frequency;

	fold_frequency = 4.0f;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			fold_effect = (fabs(sinf((((float)x / fdf->width) * fold_frequency
								+ g_obj_effects.time_accumulator) * M_PI))
					+ fabs(sinf((((float)y / fdf->height) * fold_frequency
								+ g_obj_effects.time_accumulator * 0.7f)
							* M_PI))) * 20.0f * g_obj_effects.intensity;
			fdf->points[index] = g_obj_effects.original_points[index]
				+ fold_effect;
			x++;
		}
		y++;
	}
}

void	apply_geometric_fold_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return ;
	apply_fold_to_points(fdf);
}
