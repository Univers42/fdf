/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liquid_metal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:21:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:25:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;


// Apply liquid metal background - chrome-like flowing effect
void    apply_liquid_metal_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Flowing metal waves
			float flow1 = sinf((norm_x * 6.0f + norm_y * 2.0f + time * 2.0f) * M_PI);
			float flow2 = sinf((norm_x * 8.0f - norm_y * 3.0f + time * 1.5f) * M_PI);
			float flow3 = sinf((norm_x * 4.0f + norm_y * 4.0f + time * 3.0f) * M_PI);
			
			// Combine flows for metallic reflection
			float metal_reflection = (flow1 + flow2 + flow3) / 3.0f;
			metal_reflection = (metal_reflection + 1.0f) / 2.0f; // Normalize
			
			// Metallic colors - silver, chrome, steel
			uint32_t dark_metal = 0x333333;
			uint32_t medium_metal = 0x888888;
			uint32_t bright_metal = 0xCCCCCC;
			uint32_t chrome_highlight = 0xFFFFFF;
			
			if (metal_reflection > 0.85f)
				buffer[index] = chrome_highlight;
			else if (metal_reflection > 0.6f)
				buffer[index] = lerp_color(bright_metal, chrome_highlight, (metal_reflection - 0.6f) * 4.0f);
			else if (metal_reflection > 0.3f)
				buffer[index] = lerp_color(medium_metal, bright_metal, (metal_reflection - 0.3f) * 3.33f);
			else
				buffer[index] = lerp_color(dark_metal, medium_metal, metal_reflection * 3.33f);
		}
	}
}
