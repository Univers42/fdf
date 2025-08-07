/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brick_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Brick texture - rectangular pattern with mortar
void    apply_brick_texture(t_app *fdf)
{
	float brick_width = 12.0f / g_texture.scale_factor;
	float brick_height = 6.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Brick grid calculation
			int row = (int)(y / brick_height);
			int col = (int)((x + (row % 2) * brick_width / 2) / brick_width);
			
			// Mortar lines
			float local_x = fmodf(x + (row % 2) * brick_width / 2, brick_width);
			float local_y = fmodf(y, brick_height);
			
			bool is_mortar = (local_x < 1.0f || local_x > brick_width - 1.0f || 
							 local_y < 1.0f || local_y > brick_height - 1.0f);
			
			uint32_t texture_color;
			if (is_mortar)
				texture_color = 0xD3D3D3; // Light gray mortar
			else
			{
				// Vary brick colors
				int brick_id = (row * 1000 + col) % 3;
				switch (brick_id)
				{
					case 0: texture_color = 0xB22222; break; // Fire brick
					case 1: texture_color = 0xA0522D; break; // Sienna
					case 2: texture_color = 0x8B4513; break; // Saddle brown
					default: texture_color = 0xB22222; break;
				}
			}
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}
