/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distortion_effect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Apply depth distortion effect - warps depth based on position
void apply_depth_distortion_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Normalize coordinates
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create depth distortion pattern
			float distortion = sinf((norm_x + norm_y + g_obj_effects.time_accumulator) * M_PI * 4.0f);
			distortion *= g_obj_effects.intensity * 25.0f;
			
			fdf->points[index] = g_obj_effects.original_points[index] + distortion;
		}
	}
}
