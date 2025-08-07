/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Stripes texture - dynamic color bands
void apply_stripes_texture(t_app *fdf)
{
	float stripe_width = 6.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Diagonal stripes with animation
			float diagonal_pos = (x + y + g_texture.time_accumulator * 20.0f) / stripe_width;
			int stripe_id = (int)diagonal_pos % 3;
			
			uint32_t texture_color;
			switch (stripe_id)
			{
				case 0: texture_color = 0xFF0000; break; // Red
				case 1: texture_color = 0x00FF00; break; // Green
				case 2: texture_color = 0x0000FF; break; // Blue
				default: texture_color = 0xFFFFFF; break;
			}
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.5f);
		}
	}
}


