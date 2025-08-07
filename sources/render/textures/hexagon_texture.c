/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexagon_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:48:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Hexagon texture - honeycomb pattern
void apply_hexagon_texture(t_app *fdf)
{
	float hex_size = 10.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Hexagonal grid calculation (simplified)
			float hex_x = x / hex_size;
			float hex_y = y / hex_size;
			
			// Approximate hexagon pattern
			int grid_x = (int)hex_x;
			int grid_y = (int)hex_y;
			
			// Offset every other row
			if (grid_y % 2 == 1)
				grid_x += 0.5f;
			
			// Distance from hexagon center
			float local_x = hex_x - floorf(hex_x) - 0.5f;
			float local_y = hex_y - floorf(hex_y) - 0.5f;
			float dist = fmaxf(fabsf(local_x), fabsf(local_y) * 0.866f);
			
			bool is_border = dist > 0.4f;
			bool is_center = dist < 0.1f;
			
			uint32_t texture_color;
			if (is_center)
				texture_color = 0xFFD700; // Gold center
			else if (is_border)
				texture_color = 0x000000; // Black border
			else
				texture_color = 0xFFA500; // Orange fill
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}