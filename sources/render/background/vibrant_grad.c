/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vibrant_grad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:21:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:22:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply vibrant gradient background - rainbow waves
void    apply_vibrant_gradient_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			// Normalize coordinates
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Create moving rainbow waves
			float wave1 = sinf((norm_x * 4.0f + time * 2.0f) * M_PI);
			float wave2 = sinf((norm_y * 3.0f + time * 1.5f) * M_PI);
			float wave3 = sinf(((norm_x + norm_y) * 2.0f + time * 3.0f) * M_PI);
			
			// Combine waves for color selection
			float color_factor = (wave1 + wave2 + wave3) / 3.0f;
			color_factor = (color_factor + 1.0f) / 2.0f; // Normalize to [0,1]
			
			// Rainbow spectrum
			uint32_t colors[] = {
				0xFF0000, // Red
				0xFF8000, // Orange
				0xFFFF00, // Yellow
				0x00FF00, // Green
				0x00FFFF, // Cyan
				0x0000FF, // Blue
				0x8000FF, // Purple
				0xFF00FF  // Magenta
			};
			
			int color_idx = (int)(color_factor * 7.0f);
			float local_t = (color_factor * 7.0f) - color_idx;
			
			if (color_idx >= 7) { color_idx = 6; local_t = 1.0f; }
			
			buffer[index] = lerp_color(colors[color_idx], colors[color_idx + 1], local_t);
		}
	}
}

