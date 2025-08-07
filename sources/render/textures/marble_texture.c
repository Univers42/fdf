/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Marble texture - swirling veins
void apply_marble_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Marble vein pattern
			float vein1 = sinf((norm_x * 6.0f + norm_y * 4.0f + g_texture.time_accumulator * 0.3f) * M_PI);
			float vein2 = sinf((norm_x * 8.0f - norm_y * 6.0f + g_texture.time_accumulator * 0.2f) * M_PI);
			float vein3 = sinf((norm_x * 12.0f + norm_y * 8.0f) * M_PI);
			
			float marble_intensity = (vein1 + vein2 + vein3) / 3.0f;
			marble_intensity = (marble_intensity + 1.0f) / 2.0f;
			
			// Marble colors - white to gray with dark veins
			uint32_t white_marble = 0xF8F8FF;
			uint32_t gray_marble = 0xC0C0C0;
			uint32_t dark_vein = 0x696969;
			
			uint32_t texture_color;
			if (marble_intensity > 0.8f)
				texture_color = white_marble;
			else if (marble_intensity < 0.2f)
				texture_color = dark_vein;
			else
				texture_color = gray_marble;
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}