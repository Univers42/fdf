/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosmic_nebula.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:25:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:29:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system  g_dynamic_bg;

// Apply cosmic nebula background - space clouds
void apply_cosmic_nebula_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multiple nebula layers with different scales and speeds
			float nebula1 = sinf((norm_x * 4.0f + time * 0.3f) * M_PI) * 
						   cosf((norm_y * 3.0f + time * 0.2f) * M_PI);
			float nebula2 = sinf((norm_x * 8.0f + time * 0.5f) * M_PI) * 
						   cosf((norm_y * 6.0f + time * 0.4f) * M_PI);
			float nebula3 = sinf((norm_x * 12.0f + time * 0.8f) * M_PI) * 
						   cosf((norm_y * 10.0f + time * 0.6f) * M_PI);
			
			// Combine nebula layers
			float nebula_density = (nebula1 * 0.5f + nebula2 * 0.3f + nebula3 * 0.2f);
			nebula_density = (nebula_density + 1.0f) / 2.0f; // Normalize
			
			// Add distance effect (center is brighter)
			float center_dist = sqrtf((norm_x - 0.5f) * (norm_x - 0.5f) + (norm_y - 0.5f) * (norm_y - 0.5f));
			float center_glow = 1.0f - center_dist;
			nebula_density *= center_glow;
			
			// Cosmic colors
			uint32_t space_black = 0x000000;
			uint32_t dark_purple = 0x200040;
			uint32_t bright_purple = 0x8000FF;
			uint32_t pink = 0xFF0080;
			uint32_t white_core = 0xFFFFFF;
			
			if (nebula_density > 0.8f)
				buffer[index] = lerp_color(bright_purple, white_core, (nebula_density - 0.8f) * 5.0f);
			else if (nebula_density > 0.6f)
				buffer[index] = lerp_color(pink, bright_purple, (nebula_density - 0.6f) * 5.0f);
			else if (nebula_density > 0.3f)
				buffer[index] = lerp_color(dark_purple, pink, (nebula_density - 0.3f) * 3.33f);
			else if (nebula_density > 0.1f)
				buffer[index] = lerp_color(space_black, dark_purple, (nebula_density - 0.1f) * 5.0f);
			else
				buffer[index] = space_black;
		}
	}
}
