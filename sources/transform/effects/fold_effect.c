/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fold_effect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:12:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_fold_to_points(t_app *fdf)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	t_point2						coord;
	int								index;
	float							fold_effect;
	float							fold_frequency;

	fold_frequency = 4.0f;
	coord.y = -1;
	while (++coord.y < fdf->height)
	{
		coord.x = -1;
		while (++coord.x < fdf->width)
		{
			index = coord.y * fdf->width + coord.x;
			fold_effect = (fabs(sinf((((float)coord.x / fdf->width)
								* fold_frequency
								+ oe->time_accumulator) * M_PI))
					+ fabs(sinf((((float)coord.y / fdf->height)
								* fold_frequency
								+ oe->time_accumulator * 0.7f)
							* M_PI))) * 20.0f * oe->intensity;
			fdf->points[index] = oe->original_points[index] + fold_effect;
		}
	}
}

void	apply_geometric_fold_effect(t_app *fdf)
{
	if (!gobjfx(NULL)->original_points)
		return ;
	apply_fold_to_points(fdf);
}
