/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epileptic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:21:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:27:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply epileptic flash background - WARNING: SEIZURE TRIGGER
void apply_epileptic_flash_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	// Fast flashing colors
	float flash_freq = 20.0f; // Very fast flashing
	float flash_phase = sinf(time * flash_freq);
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multiple flashing patterns
			float pattern1 = sinf((norm_x * 10.0f + time * 25.0f) * M_PI);
			float pattern2 = cosf((norm_y * 8.0f + time * 30.0f) * M_PI);
			float pattern3 = sinf(((norm_x + norm_y) * 15.0f + time * 40.0f) * M_PI);
			
			// Combine patterns
			float flash_intensity = (pattern1 + pattern2 + pattern3 + flash_phase) / 4.0f;
			flash_intensity = (flash_intensity + 1.0f) / 2.0f;
			
			// High contrast flashing colors
			uint32_t colors[] = {0x000000, 0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF};
			int color_idx = (int)(flash_intensity * 7.0f) % 8;
			
			buffer[index] = colors[color_idx];
		}
	}
}

