/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:49:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_geometric_pulse_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float pulse = 1.0f + 0.3f * sinf(g_obj_effects.time_accumulator * 3.0f) * g_obj_effects.intensity;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Apply pulsing scale to Z coordinate
			fdf->points[index] = g_obj_effects.original_points[index] * pulse;
		}
	}
}