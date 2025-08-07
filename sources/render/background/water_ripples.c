/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   water_ripples.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:21:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:27:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply water ripples background - realistic water simulation
void apply_water_ripples_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multiple ripple sources
			float ripple1_x = 0.3f + 0.2f * sinf(time * 0.8f);
			float ripple1_y = 0.4f + 0.2f * cosf(time * 0.6f);
			float ripple2_x = 0.7f + 0.15f * sinf(time * 1.2f);
			float ripple2_y = 0.6f + 0.15f * cosf(time * 0.9f);
			float ripple3_x = 0.5f + 0.1f * sinf(time * 1.5f);
			float ripple3_y = 0.3f + 0.1f * cosf(time * 1.1f);
			
			// Calculate distances to ripple sources
			float dist1 = sqrtf((norm_x - ripple1_x) * (norm_x - ripple1_x) + 
							   (norm_y - ripple1_y) * (norm_y - ripple1_y));
			float dist2 = sqrtf((norm_x - ripple2_x) * (norm_x - ripple2_x) + 
							   (norm_y - ripple2_y) * (norm_y - ripple2_y));
			float dist3 = sqrtf((norm_x - ripple3_x) * (norm_x - ripple3_x) + 
							   (norm_y - ripple3_y) * (norm_y - ripple3_y));
			
			// Create ripple waves
			float wave1 = sinf((dist1 * 30.0f - time * 8.0f) * M_PI) * expf(-dist1 * 3.0f);
			float wave2 = sinf((dist2 * 25.0f - time * 6.0f) * M_PI) * expf(-dist2 * 4.0f);
			float wave3 = sinf((dist3 * 35.0f - time * 10.0f) * M_PI) * expf(-dist3 * 5.0f);
			
			// Combine waves
			float water_height = (wave1 + wave2 + wave3) * 0.5f + 0.5f;
			water_height = fmaxf(0.0f, fminf(1.0f, water_height));
			
			// Water colors from deep to shallow
			uint32_t deep_water = 0x001133;
			uint32_t shallow_water = 0x4488BB;
			uint32_t foam = 0xAADDFF;
			
			if (water_height > 0.8f)
				buffer[index] = lerp_color(shallow_water, foam, (water_height - 0.8f) * 5.0f);
			else
				buffer[index] = lerp_color(deep_water, shallow_water, water_height);
		}
	}
}
