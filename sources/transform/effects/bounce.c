/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:14:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>



// Apply INSANE bounce dance move - object bounces with extreme deformation
void apply_dance_bounce(t_app *fdf)
{
	float bounce_freq = 8.0f * g_dance.rhythm_multiplier; // Super fast bouncing!
	float bounce_height = 50.0f * g_dance.move_intensity;
	
	// Vertical bouncing motion with EXTREME amplitude
	float bounce_y = sinf(g_dance.time_accumulator * bounce_freq) * bounce_height;
	
	// CRAZY squash and stretch effect
	float squash_factor = 1.0f + (sinf(g_dance.time_accumulator * bounce_freq * 2.0f) * 0.8f);
	
	// Apply bounce translation
	transformation_stack_translate(&fdf->transformation_stack, 0, bounce_y * 0.2f, 0);
	
	// Apply EXTREME squash/stretch to geometry
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float original_z = g_dance.original_points[index];
			
			// Distance from center affects squash intensity
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			float dist_from_center = sqrtf((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));
			float max_dist = sqrtf(center_x * center_x + center_y * center_y);
			float dist_factor = 1.0f - (dist_from_center / max_dist);
			
			// Extreme squash effect with distance falloff
			float final_squash = squash_factor * (1.0f + dist_factor * 2.0f);
			fdf->points[index] = original_z * final_squash;
		}
	}
}
