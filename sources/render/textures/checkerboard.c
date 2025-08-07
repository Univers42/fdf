/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Checkerboard texture - classic black and white squares
void apply_checkerboard_texture(t_app *fdf)
{
	float checker_size = 8.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Create checkerboard pattern
			int checker_x = (int)(x / checker_size);
			int checker_y = (int)(y / checker_size);
			
			bool is_white = ((checker_x + checker_y) % 2) == 0;
			uint32_t texture_color = is_white ? 0xFFFFFF : 0x000000;
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}


