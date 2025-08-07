/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Apply CRAZY spin dance move - object spins while doing geometric transformations
void apply_dance_spin(t_app *fdf)
{
	float spin_speed = 0.15f * g_dance.rhythm_multiplier; // Much faster!
	
	// MULTIPLE axis rotations for crazy spinning
	transformation_stack_rotate_y(&fdf->transformation_stack, spin_speed);
	transformation_stack_rotate_x(&fdf->transformation_stack, spin_speed * 0.7f);
	transformation_stack_rotate_z(&fdf->transformation_stack, spin_speed * 0.3f);
	
	// Add WILD geometric deformation while spinning
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create SPINNING wave effect
			float spiral_angle = sqrtf(norm_x * norm_x + norm_y * norm_y) * 8.0f + g_dance.time_accumulator * 5.0f;
			float spiral_effect = sinf(spiral_angle) * 30.0f * g_dance.move_intensity;
			
			fdf->points[index] = g_dance.original_points[index] + spiral_effect;
		}
	}
}
