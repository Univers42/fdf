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
	int		y;
	int		x;
	int		index;
	float	distor;

	if (!g_obj_effects.original_points)
		return ;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			distor = sinf((((float)x / fdf->width) + ((float)y / fdf->height)
						+ g_obj_effects.time_accumulator) * M_PI * 4.0f);
			distor *= g_obj_effects.intensity * 25.0f;
			fdf->points[index] = g_obj_effects.original_points[index]
				+ distor;
			x++;
		}
		y++;
	}
}
