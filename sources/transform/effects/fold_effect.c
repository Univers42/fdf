/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fold_effect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply geometric fold effect - creates folding patterns
void apply_geometric_fold_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float fold_frequency = 4.0f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create folding pattern
			float fold1 = fabs(sinf((norm_x * fold_frequency + g_obj_effects.time_accumulator) * M_PI));
			float fold2 = fabs(sinf((norm_y * fold_frequency + g_obj_effects.time_accumulator * 0.7f) * M_PI));
			
			float fold_effect = (fold1 + fold2) * 20.0f * g_obj_effects.intensity;
			
			fdf->points[index] = g_obj_effects.original_points[index] + fold_effect;
		}
	}
}
