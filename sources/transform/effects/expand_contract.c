/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_contract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply height oscillation effect - oscillates based on original height
void apply_height_oscillation_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float original_z = g_obj_effects.original_points[index];
			
			// Oscillation based on original height
			float height_factor = original_z / 100.0f; // Normalize
			float oscillation = sinf(g_obj_effects.time_accumulator * 3.0f + height_factor) * 15.0f;
			
			fdf->points[index] = original_z + oscillation * g_obj_effects.intensity;
		}
	}
}
