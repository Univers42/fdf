/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:04:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply EXTREME twist dance move - object performs corkscrew motion
void apply_dance_twist(t_app *fdf)
{
	float twist_speed = 0.2f * g_dance.rhythm_multiplier; // Much faster!
	float twist_amplitude = 60.0f * g_dance.move_intensity;
	
	// INSANE corkscrew rotation on all axes
	transformation_stack_rotate_y(&fdf->transformation_stack, twist_speed);
	transformation_stack_rotate_x(&fdf->transformation_stack, twist_speed * 0.8f);
	transformation_stack_rotate_z(&fdf->transformation_stack, twist_speed * 0.6f);
	
	// EXTREME spiral deformation
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			
			float dx = x - center_x;
			float dy = y - center_y;
			float distance = sqrtf(dx * dx + dy * dy);
			
			// CRAZY spiral twist based on distance and time
			float twist_factor = distance * 0.2f + g_dance.time_accumulator * twist_speed * 20.0f;
			float twist_effect = sinf(twist_factor) * twist_amplitude;
			
			// Add secondary twist for more chaos
			float secondary_twist = cosf(twist_factor * 1.7f + g_dance.time_accumulator * 3.0f) * twist_amplitude * 0.6f;
			
			fdf->points[index] = g_dance.original_points[index] + twist_effect + secondary_twist;
		}
	}
}