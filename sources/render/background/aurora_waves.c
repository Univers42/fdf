/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aurora_waves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:26:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:27:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system  g_dynamic_bg;

// Apply aurora waves background - northern lights effect
void    apply_aurora_waves_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Aurora waves flowing horizontally
			float wave1 = sinf((norm_y * 8.0f + norm_x * 2.0f + time * 2.0f) * M_PI);
			float wave2 = sinf((norm_y * 12.0f + norm_x * 1.5f + time * 1.5f) * M_PI);
			float wave3 = sinf((norm_y * 6.0f + norm_x * 3.0f + time * 3.0f) * M_PI);
			
			// Combine waves for aurora intensity
			float aurora_intensity = (wave1 + wave2 + wave3) / 3.0f;
			aurora_intensity = (aurora_intensity + 1.0f) / 2.0f; // Normalize
			
			// Vertical gradient (aurora is stronger at top)
			float height_factor = 1.0f - norm_y;
			aurora_intensity *= height_factor * height_factor;
			
			// Aurora colors
			uint32_t dark_sky = 0x000011;
			uint32_t green_aurora = 0x00FF44;
			uint32_t blue_aurora = 0x0044FF;
			uint32_t purple_aurora = 0x8844FF;
			
			// Color selection based on wave patterns
			if (aurora_intensity > 0.7f)
				buffer[index] = lerp_color(green_aurora, purple_aurora, (aurora_intensity - 0.7f) * 3.33f);
			else if (aurora_intensity > 0.4f)
				buffer[index] = lerp_color(blue_aurora, green_aurora, (aurora_intensity - 0.4f) * 3.33f);
			else if (aurora_intensity > 0.1f)
				buffer[index] = lerp_color(dark_sky, blue_aurora, (aurora_intensity - 0.1f) * 3.33f);
			else
				buffer[index] = dark_sky;
		}
	}
}

