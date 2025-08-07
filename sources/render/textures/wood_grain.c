/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wood_grain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Wood grain texture - organic flowing lines
void apply_wood_grain_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Wood grain pattern with multiple frequencies
			float grain1 = sinf((norm_x * 20.0f + g_texture.time_accumulator * 0.5f) * M_PI);
			float grain2 = sinf((norm_y * 8.0f + norm_x * 2.0f) * M_PI);
			float grain3 = sinf((norm_x * 40.0f + grain1 * 5.0f) * M_PI);
			
			float wood_intensity = (grain1 + grain2 + grain3) / 3.0f;
			wood_intensity = (wood_intensity + 1.0f) / 2.0f; // Normalize to [0,1]
			
			// Wood colors - light to dark brown
			uint32_t light_wood = 0xDEB887; // Burlywood
			uint32_t dark_wood = 0x8B4513;  // Saddle brown
			
			uint32_t texture_color = blend_colors(light_wood, dark_wood, wood_intensity);
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}
