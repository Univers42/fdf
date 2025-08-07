/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dramatic_clousds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:20:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:20:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply dramatic clouds background - stormy atmosphere
void apply_dramatic_clouds_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multi-layer noise for cloud effect
			float cloud1 = sinf((norm_x * 8.0f + time * 0.5f) * M_PI) * 
						  cosf((norm_y * 6.0f + time * 0.3f) * M_PI);
			float cloud2 = sinf((norm_x * 15.0f + time * 0.8f) * M_PI) * 
						  cosf((norm_y * 12.0f + time * 0.6f) * M_PI);
			float cloud3 = sinf(((norm_x + norm_y) * 20.0f + time * 1.2f) * M_PI);
			
			// Combine cloud layers
			float cloud_density = (cloud1 * 0.5f + cloud2 * 0.3f + cloud3 * 0.2f);
			cloud_density = (cloud_density + 1.0f) / 2.0f; // Normalize
			
			// Dark stormy colors
			uint32_t dark_cloud = 0x202030;
			uint32_t light_cloud = 0x808090;
			uint32_t lightning = 0xFFFFBB;
			
			// Add lightning flashes
			float lightning_chance = sinf(time * 15.0f + norm_x * 50.0f);
			if (lightning_chance > 0.98f && cloud_density > 0.7f)
			{
				buffer[index] = lightning;
			}
			else
			{
				buffer[index] = lerp_color(dark_cloud, light_cloud, cloud_density);
			}
		}
	}
}