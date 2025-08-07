/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow_vortex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:21:20 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:24:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply rainbow vortex background - spiraling colors
void apply_rainbow_vortex_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH - 0.5f;
			float norm_y = (float)y / WIN_HEIGHT - 0.5f;
			
			// Convert to polar coordinates
			float radius = sqrtf(norm_x * norm_x + norm_y * norm_y);
			float angle = atan2f(norm_y, norm_x);
			
			// Create vortex spiral
			float spiral_angle = angle + radius * 8.0f - time * 4.0f;
			
			// Color based on spiral position
			float color_position = fmodf(spiral_angle / (2.0f * M_PI) + 1.0f, 1.0f);
			
			// Rainbow colors
			uint32_t colors[] = {
				0xFF0000, // Red
				0xFF8000, // Orange
				0xFFFF00, // Yellow
				0x00FF00, // Green
				0x00FFFF, // Cyan
				0x0000FF, // Blue
				0x8000FF, // Purple
				0xFF0000  // Back to red
			};
			
			int color_idx = (int)(color_position * 7.0f);
			float local_t = (color_position * 7.0f) - color_idx;
			
			uint32_t base_color = lerp_color(colors[color_idx], colors[color_idx + 1], local_t);
			
			// Add radial fade
			float fade = 1.0f - radius;
			if (fade < 0.0f) fade = 0.0f;
			
			uint8_t r = ((base_color >> 16) & 0xFF) * fade;
			uint8_t g = ((base_color >> 8) & 0xFF) * fade;
			uint8_t b = (base_color & 0xFF) * fade;
			
			buffer[index] = (r << 16) | (g << 8) | b;
		}
	}
}
