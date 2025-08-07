/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal_brushed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:33 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Brushed metal texture - horizontal lines with highlights
void apply_metal_brushed_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Horizontal brush lines
			float brush_lines = sinf(norm_y * 80.0f * g_texture.scale_factor) * 0.3f;
			
			// Add subtle highlights
			float highlight = sinf((norm_x + g_texture.time_accumulator * 0.8f) * M_PI * 4.0f) * 0.2f;
			
			float metal_intensity = 0.5f + brush_lines + highlight;
			metal_intensity = fmaxf(0.0f, fminf(1.0f, metal_intensity));
			
			// Metal colors - dark to bright silver
			uint32_t dark_metal = 0x404040;
			uint32_t bright_metal = 0xC0C0C0;
			
			uint32_t texture_color = blend_colors(dark_metal, bright_metal, metal_intensity);
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.8f);
		}
	}
}
