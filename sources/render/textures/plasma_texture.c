/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plasma_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Plasma texture - animated energy field
void apply_plasma_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Multiple plasma waves
			float plasma1 = sinf((norm_x * 8.0f + g_texture.time_accumulator * 2.0f) * M_PI);
			float plasma2 = sinf((norm_y * 6.0f + g_texture.time_accumulator * 1.5f) * M_PI);
			float plasma3 = sinf(((norm_x + norm_y) * 10.0f + g_texture.time_accumulator * 3.0f) * M_PI);
			float plasma4 = sinf((sqrtf(norm_x * norm_x + norm_y * norm_y) * 12.0f - g_texture.time_accumulator * 4.0f) * M_PI);
			
			float plasma_intensity = (plasma1 + plasma2 + plasma3 + plasma4) / 4.0f;
			plasma_intensity = (plasma_intensity + 1.0f) / 2.0f; // Normalize to [0,1]
			
			// Plasma colors - blue to red spectrum
			uint32_t texture_color;
			if (plasma_intensity < 0.33f)
				texture_color = blend_colors(0x0000FF, 0x00FFFF, plasma_intensity * 3.0f); // Blue to cyan
			else if (plasma_intensity < 0.66f)
				texture_color = blend_colors(0x00FFFF, 0xFFFF00, (plasma_intensity - 0.33f) * 3.0f); // Cyan to yellow
			else
				texture_color = blend_colors(0xFFFF00, 0xFF0000, (plasma_intensity - 0.66f) * 3.0f); // Yellow to red
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.8f);
		}
	}
}