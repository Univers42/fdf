/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_heart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_heart_transformation(t_app *fdf)
{
	float heart_scale = fminf(fdf->width, fdf->height) / 4.0f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Map to heart coordinates (centered and scaled)
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			// Flip Y to have heart point down
			norm_y = -norm_y;
			
			float heart_x = norm_x * heart_scale;
			float heart_y = norm_y * heart_scale;
			float heart_z = 0.0f;
			
			float x_scaled = norm_x * 2.0f;
			float y_scaled = norm_y * 1.5f;
			
			// Upper heart lobes
			if (y_scaled > 0.0f)
			{
				float lobe1_center = -0.5f;
				float lobe2_center = 0.5f;
				float lobe_y_center = 0.3f;
				
				float dist1 = sqrtf((x_scaled - lobe1_center)*(x_scaled - lobe1_center) + 
								   (y_scaled - lobe_y_center)*(y_scaled - lobe_y_center));
				float dist2 = sqrtf((x_scaled - lobe2_center)*(x_scaled - lobe2_center) + 
								   (y_scaled - lobe_y_center)*(y_scaled - lobe_y_center));
				
				float lobe_radius = 0.6f;
				if (dist1 < lobe_radius || dist2 < lobe_radius)
				{
					float height1 = (dist1 < lobe_radius) ? sqrtf(lobe_radius*lobe_radius - dist1*dist1) : 0.0f;
					float height2 = (dist2 < lobe_radius) ? sqrtf(lobe_radius*lobe_radius - dist2*dist2) : 0.0f;
					heart_z = fmaxf(height1, height2) * heart_scale * 0.3f;
				}
			}
			// Lower heart point
			else if (y_scaled < 0.0f)
			{
				float point_factor = 1.0f + y_scaled;
				if (point_factor > 0.0f && fabsf(x_scaled) < point_factor * 0.8f)
				{
					float point_width = point_factor * 0.8f;
					float dist_from_center_line = fabsf(x_scaled);
					if (dist_from_center_line < point_width)
					{
						heart_z = heart_scale * 0.2f * point_factor * 
								 (1.0f - dist_from_center_line / point_width);
					}
				}
			}
			// Middle section - close the gap between lobes and point
			else
			{
				if (fabsf(x_scaled) < 0.8f)
				{
					heart_z = heart_scale * 0.15f * (0.8f - fabsf(x_scaled));
				}
			}
			
			// Add heart volume with smooth falloff
			float overall_dist = sqrtf(norm_x*norm_x + norm_y*norm_y);
			if (overall_dist < 1.5f)
			{
				float volume_factor = 1.0f - overall_dist / 1.5f;
				heart_z += heart_scale * 0.1f * volume_factor * volume_factor;
			}
			
			// Close the base of the heart
			if (heart_z > 0.0f && overall_dist > 1.2f && overall_dist < 1.5f)
			{
				float base_factor = (1.5f - overall_dist) / 0.3f;
				heart_z = heart_scale * 0.05f * base_factor; // Base/bottom connection
			}
			
			// Add original terrain as texture detail
			heart_z += fdf->points[index] * 0.02f;
			
			// Apply transformation matrix
			float sp[4] = {heart_x, heart_y, heart_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
