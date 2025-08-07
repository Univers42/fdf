/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_scatter_effect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:16:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>


// Apply vertex scatter effect - randomly displaces vertices
void apply_vertex_scatter_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	static float *noise_offsets = NULL;
	if (!noise_offsets)
	{
		noise_offsets = malloc(sizeof(float) * g_obj_effects.total_points);
		for (int i = 0; i < g_obj_effects.total_points; i++)
			noise_offsets[i] = (float)rand() / (float)RAND_MAX;
	}
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Create smooth random displacement
			float noise = sinf(g_obj_effects.time_accumulator * 2.0f + noise_offsets[index] * M_PI * 2.0f);
			float scatter = noise * 25.0f * g_obj_effects.intensity;
			
			fdf->points[index] = g_obj_effects.original_points[index] + scatter;
		}
	}
}
