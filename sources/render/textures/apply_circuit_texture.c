/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_circuit_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:48:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Circuit board texture - electronic traces
void apply_circuit_board_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Circuit traces - horizontal and vertical lines
			bool h_trace = (y % 8 == 0 || y % 8 == 1);
			bool v_trace = (x % 12 == 0 || x % 12 == 1);
			bool junction = ((x % 12 < 3) && (y % 8 < 3));
			
			// Add some animated elements
			bool active_trace = ((x + y + (int)(g_texture.time_accumulator * 10.0f)) % 20) < 2;
			
			uint32_t texture_color;
			if (junction)
				texture_color = 0xFFD700; // Gold junction
			else if ((h_trace || v_trace) && active_trace)
				texture_color = 0x00FF00; // Active green trace
			else if (h_trace || v_trace)
				texture_color = 0x00AA00; // Inactive green trace
			else
				texture_color = 0x006600; // Dark green PCB
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}