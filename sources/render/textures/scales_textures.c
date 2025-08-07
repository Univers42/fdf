/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scales_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:38 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Scales texture - fish/dragon scale pattern
void apply_scales_texture(t_app *fdf)
{
	float scale_size = 8.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Scale pattern with offset rows
			float scale_x = x / scale_size;
			float scale_y = y / scale_size;
			
			// Offset every other row
			if ((int)scale_y % 2 == 1)
				scale_x += 0.5f;
			
			// Distance from scale center
			float local_x = scale_x - floorf(scale_x) - 0.5f;
			float local_y = scale_y - floorf(scale_y) - 0.5f;
			float dist = sqrtf(local_x * local_x + local_y * local_y);
			
			// Scale highlight based on distance and animation
			float highlight = 1.0f - dist * 2.0f;
			highlight = fmaxf(0.0f, highlight);
			
			// Add shimmer effect
			float shimmer = sinf((norm_x * 10.0f + norm_y * 8.0f + g_texture.time_accumulator * 3.0f) * M_PI);
			highlight += shimmer * 0.2f;
			
			// Scale colors
			uint32_t dark_scale = 0x2F4F4F;  // Dark slate gray
			uint32_t bright_scale = 0x87CEEB; // Sky blue
			
			uint32_t texture_color = blend_colors(dark_scale, bright_scale, highlight);
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}

