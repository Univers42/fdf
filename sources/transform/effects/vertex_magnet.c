/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_magnet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Apply vertex magnet effect - attracts vertices to moving points
void apply_vertex_magnet_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	// Moving magnet positions
	float magnet1_x = (sinf(g_obj_effects.time_accumulator * 0.8f) + 1.0f) * fdf->width * 0.5f;
	float magnet1_y = (cosf(g_obj_effects.time_accumulator * 0.6f) + 1.0f) * fdf->height * 0.5f;
	
	float magnet2_x = (sinf(g_obj_effects.time_accumulator * 1.2f + M_PI) + 1.0f) * fdf->width * 0.5f;
	float magnet2_y = (cosf(g_obj_effects.time_accumulator * 0.9f + M_PI) + 1.0f) * fdf->height * 0.5f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Calculate distances to magnets
			float dx1 = x - magnet1_x;
			float dy1 = y - magnet1_y;
			float dist1 = sqrtf(dx1 * dx1 + dy1 * dy1) + 1.0f; // +1 to avoid division by zero
			
			float dx2 = x - magnet2_x;
			float dy2 = y - magnet2_y;
			float dist2 = sqrtf(dx2 * dx2 + dy2 * dy2) + 1.0f;
			
			// Calculate magnetic forces
			float force1 = 500.0f / (dist1 * dist1);
			float force2 = -300.0f / (dist2 * dist2); // Repelling magnet
			
			float total_force = (force1 + force2) * g_obj_effects.intensity;
			
			fdf->points[index] = g_obj_effects.original_points[index] + total_force;
		}
	}
}
