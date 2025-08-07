/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_plasma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:21:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:27:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply fire plasma background - dynamic fire effect
void apply_fire_plasma_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Fire rises from bottom
			float fire_base = 1.0f - norm_y;
			
			// Turbulent fire pattern
			float turbulence1 = sinf((norm_x * 8.0f + time * 4.0f) * M_PI);
			float turbulence2 = sinf((norm_x * 15.0f + time * 6.0f) * M_PI);
			float turbulence3 = sinf((norm_y * 12.0f + time * 5.0f) * M_PI);
			
			float fire_intensity = fire_base * (0.7f + 0.3f * (turbulence1 + turbulence2 + turbulence3) / 3.0f);
			fire_intensity = fmaxf(0.0f, fminf(1.0f, fire_intensity));
			
			// Fire color gradient
			uint32_t black = 0x000000;
			uint32_t dark_red = 0x330000;
			uint32_t red = 0xFF0000;
			uint32_t orange = 0xFF4400;
			uint32_t yellow = 0xFFFF00;
			uint32_t white = 0xFFFFFF;
			
			if (fire_intensity < 0.2f)
				buffer[index] = lerp_color(black, dark_red, fire_intensity * 5.0f);
			else if (fire_intensity < 0.4f)
				buffer[index] = lerp_color(dark_red, red, (fire_intensity - 0.2f) * 5.0f);
			else if (fire_intensity < 0.6f)
				buffer[index] = lerp_color(red, orange, (fire_intensity - 0.4f) * 5.0f);
			else if (fire_intensity < 0.8f)
				buffer[index] = lerp_color(orange, yellow, (fire_intensity - 0.6f) * 5.0f);
			else
				buffer[index] = lerp_color(yellow, white, (fire_intensity - 0.8f) * 5.0f);
		}
	}
}



