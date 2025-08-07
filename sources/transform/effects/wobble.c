/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:16:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_dance_wobble(t_app *fdf)
{
	float wobble_freq = 8.0f * g_dance.rhythm_multiplier; // SUPER fast!
	float wobble_intensity = g_dance.move_intensity;
	
	// INSANE multi-frequency wobbling on ALL axes
	float wobble_x = (sinf(g_dance.time_accumulator * wobble_freq) + 
					 sinf(g_dance.time_accumulator * wobble_freq * 2.7f) * 0.7f +
					 sinf(g_dance.time_accumulator * wobble_freq * 4.3f) * 0.4f) * 0.05f;
	float wobble_y = (cosf(g_dance.time_accumulator * wobble_freq * 1.9f) + 
					 sinf(g_dance.time_accumulator * wobble_freq * 3.1f) * 0.6f +
					 cosf(g_dance.time_accumulator * wobble_freq * 5.7f) * 0.3f) * 0.04f;
	float wobble_z = (sinf(g_dance.time_accumulator * wobble_freq * 1.4f) + 
					 cosf(g_dance.time_accumulator * wobble_freq * 3.8f) * 0.8f +
					 sinf(g_dance.time_accumulator * wobble_freq * 6.2f) * 0.2f) * 0.03f;
	
	transformation_stack_rotate_x(&fdf->transformation_stack, wobble_x * wobble_intensity);
	transformation_stack_rotate_y(&fdf->transformation_stack, wobble_y * wobble_intensity);
	transformation_stack_rotate_z(&fdf->transformation_stack, wobble_z * wobble_intensity);
	
	// EXTREME geometric wobble - total chaos!
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Multiple CHAOTIC wobble frequencies
			float wobble1 = sinf((norm_x + g_dance.time_accumulator * wobble_freq * 1.2f) * M_PI * 6.0f);
			float wobble2 = cosf((norm_y + g_dance.time_accumulator * wobble_freq * 1.8f) * M_PI * 4.0f);
			float wobble3 = sinf(((norm_x + norm_y) + g_dance.time_accumulator * wobble_freq * 2.3f) * M_PI * 5.0f);
			float wobble4 = cosf((norm_x * norm_y + g_dance.time_accumulator * wobble_freq * 0.7f) * M_PI * 8.0f);
			
			float total_wobble = (wobble1 + wobble2 + wobble3 + wobble4) * 15.0f * wobble_intensity;
			
			fdf->points[index] = g_dance.original_points[index] + total_wobble;
		}
	}
}