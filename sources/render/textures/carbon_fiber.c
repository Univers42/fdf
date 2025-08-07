/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carbon_fiber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Carbon fiber texture - woven pattern
void apply_carbon_fiber_texture(t_app *fdf)
{
	float weave_size = 4.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Weave pattern calculation
			int weave_x = (int)(x / weave_size) % 4;
			int weave_y = (int)(y / weave_size) % 4;
			
			bool is_fiber_a = ((weave_x + weave_y) % 2) == 0;
			bool is_highlight = (weave_x == 0 || weave_y == 0);
			
			uint32_t texture_color;
			if (is_highlight)
				texture_color = 0x666666; // Light carbon
			else if (is_fiber_a)
				texture_color = 0x1a1a1a; // Dark carbon
			else
				texture_color = 0x000000; // Black
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}
