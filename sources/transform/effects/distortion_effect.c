/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distor_effect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:08:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply depth distor effect - warps depth based on position
void	apply_depth_distortion_effect(t_app *fdf)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	t_point2						coord;
	int								index;
	float							distor;

	if (!oe->original_points)
		return ;
	coord.y = -1;
	while (++coord.y < fdf->height)
	{
		coord.x = -1;
		while (++coord.x < fdf->width)
		{
			index = coord.y * fdf->width + coord.x;
			distor = sinf((((float)coord.x / fdf->width)
						+ ((float)coord.y / fdf->height)
						+ oe->time_accumulator) * M_PI * 4.0f);
			distor *= oe->intensity * 25.0f;
			fdf->points[index] = oe->original_points[index] + distor;
		}
	}
}
