/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   electric_storm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:21:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:25:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply electric storm background - lightning and energy
void apply_electric_storm_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	// Dark stormy base
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		buffer[i] = 0x111122;
	
	// Add lightning bolts
	for (int bolt = 0; bolt < 5; bolt++)
	{
		// Each bolt has different timing and position
		float bolt_time = fmodf(time * 3.0f + bolt * 1.7f, 4.0f);
		
		if (bolt_time < 0.1f) // Lightning flash duration
		{
			float flash_intensity = 1.0f - (bolt_time / 0.1f);
			
			// Lightning path
			int start_x = (bolt * 200 + 100) % WIN_WIDTH;
			int start_y = 0;
			int end_x = start_x + (int)(sinf(bolt * 1.3f) * 200.0f);
			int end_y = WIN_HEIGHT;
			
			// Draw jagged lightning bolt
			for (int segment = 0; segment < 20; segment++)
			{
				float t = segment / 20.0f;
				int x = start_x + (int)((end_x - start_x) * t + sinf(t * 10.0f + bolt) * 50.0f);
				int y = start_y + (int)((end_y - start_y) * t);
				
				// Draw lightning with glow
				for (int glow = -5; glow <= 5; glow++)
				{
					for (int gy = -3; gy <= 3; gy++)
					{
						int lx = x + glow;
						int ly = y + gy;
						
						if (lx >= 0 && lx < WIN_WIDTH && ly >= 0 && ly < WIN_HEIGHT)
						{
							float glow_dist = sqrtf(glow * glow + gy * gy);
							float glow_intensity = (1.0f - glow_dist / 6.0f) * flash_intensity;
							
							if (glow_intensity > 0.0f)
							{
								uint32_t lightning_color = 0xCCCCFF; // Electric blue-white
								if (glow_dist < 1.0f)
									lightning_color = 0xFFFFFF; // Pure white core
								
								buffer[ly * WIN_WIDTH + lx] = lightning_color;
							}
						}
					}
				}
			}
		}
	}
}
