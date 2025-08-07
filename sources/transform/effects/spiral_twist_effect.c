/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spiral_twist_effect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply spiral twist effect - twists the geometry
void apply_spiral_twist_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float twist_strength = 2.0f * g_obj_effects.intensity;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Calculate twist based on distance from center and time
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			float dx = x - center_x;
			float dy = y - center_y;
			float distance = sqrtf(dx * dx + dy * dy);
			
			// Create spiral twist
			float twist_angle = distance * 0.1f + g_obj_effects.time_accumulator * twist_strength;
			float twist_effect = sinf(twist_angle) * 30.0f;
			
			fdf->points[index] = g_obj_effects.original_points[index] + twist_effect;
		}
	}
}