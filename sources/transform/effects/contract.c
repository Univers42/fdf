/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:06:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Apply CRAZY expand/contract dance move - object breathes WILDLY
void apply_dance_expand_contract(t_app *fdf)
{
	float pulse_freq = 6.0f * g_dance.rhythm_multiplier; // Much faster breathing!
	float scale_amplitude = 0.8f; // HUGE breathing effect
	float scale_factor = 1.0f + sinf(g_dance.time_accumulator * pulse_freq) * scale_amplitude * g_dance.move_intensity;
	
	// EXTREME scaling with pulsation
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float original_z = g_dance.original_points[index];
			
			// Distance-based scaling for more dramatic effect
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			float dx = (x - center_x) / center_x;
			float dy = (y - center_y) / center_y;
			float dist_factor = sqrtf(dx * dx + dy * dy);
			
			// Different scaling based on distance
			float local_scale = scale_factor * (1.0f + dist_factor * 0.5f);
			
			fdf->points[index] = original_z * local_scale;
		}
	}
	
	// Add rotation during breathing for extra effect
	float breath_rotation = sinf(g_dance.time_accumulator * pulse_freq) * 0.05f;
	transformation_stack_rotate_y(&fdf->transformation_stack, breath_rotation);
	transformation_stack_rotate_x(&fdf->transformation_stack, breath_rotation * 0.7f);
}