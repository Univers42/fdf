/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion_effect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply vertex explosion effect - vertices move away from center
void apply_vertex_explosion_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float explosion_strength = 50.0f * g_obj_effects.intensity;
	float center_x = fdf->width / 2.0f;
	float center_y = fdf->height / 2.0f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Calculate distance from center
			float dx = x - center_x;
			float dy = y - center_y;
			float distance = sqrtf(dx * dx + dy * dy);
			
			// Normalize distance
			float max_distance = sqrtf(center_x * center_x + center_y * center_y);
			float norm_distance = distance / max_distance;
			
			// Create explosion effect
			float explosion_factor = sinf(g_obj_effects.time_accumulator * 2.0f) * norm_distance;
			
			fdf->points[index] = g_obj_effects.original_points[index] + explosion_factor * explosion_strength;
		}
	}
}
