/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:54 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

// Optimized gradient calculation using integer arithmetic
static int gradient(int startcolor, int endcolor, int len, int pix)
{
	int new[3];
	int r_start, g_start, b_start;
	int r_end, g_end, b_end;
	
	// Bounds checking
	if (len <= 0 || pix < 0 || pix > len)
		return (startcolor);
		
	// Fast path for no gradient
	if (startcolor == endcolor)
		return (startcolor);
	
	// Extract RGB components using bit operations
	r_start = (startcolor >> 16) & 0xFF;
	g_start = (startcolor >> 8) & 0xFF;
	b_start = startcolor & 0xFF;
	
	r_end = (endcolor >> 16) & 0xFF;
	g_end = (endcolor >> 8) & 0xFF;
	b_end = endcolor & 0xFF;
	
	// Use integer math to avoid floating point operations
	new[0] = r_start + ((r_end - r_start) * pix) / len;
	new[1] = g_start + ((g_end - g_start) * pix) / len;
	new[2] = b_start + ((b_end - b_start) * pix) / len;
	
	// Clamp values to valid range
	if (new[0] > 255) new[0] = 255;
	if (new[0] < 0) new[0] = 0;
	if (new[1] > 255) new[1] = 255;
	if (new[1] < 0) new[1] = 0;
	if (new[2] > 255) new[2] = 255;
	if (new[2] < 0) new[2] = 0;
	
	return ((new[0] << 16) | (new[1] << 8) | new[2]);
}

// Apply depth-based shadow/fade effect to colors
void apply_depth_shadow(t_app *fdf)
{
	if (!fdf || !fdf->color || !fdf->points)
		return;
	
	int total_points = fdf->width * fdf->height;
	float z_range = (float)(fdf->max_z - fdf->min_z);
	
	// Prevent division by zero
	if (z_range <= 0)
		z_range = 1.0f;
	
	for (int i = 0; i < total_points; i++)
	{
		float z_value = fdf->points[i];
		uint32_t original_color = fdf->color[i];
		
		// Calculate depth factor (0.0 = farthest/darkest, 1.0 = closest/brightest)
		float depth_factor = (z_value - fdf->min_z) / z_range;
		
		// Clamp depth factor
		if (depth_factor < 0.0f) depth_factor = 0.0f;
		if (depth_factor > 1.0f) depth_factor = 1.0f;
		
		// Define shadow colors: from dark to original
		uint32_t shadow_color = 0x000000; // Deep shadow (black)
		uint32_t mid_shadow = 0x202020;   // Medium shadow (dark gray)
		
		// Apply different shadow levels based on depth
		if (depth_factor < 0.3f)
		{
			// Deep shadow region (farthest points)
			int gradient_pos = (int)(depth_factor * 100 / 0.3f);
			fdf->color[i] = gradient(shadow_color, mid_shadow, 100, gradient_pos);
		}
		else if (depth_factor < 0.7f)
		{
			// Medium shadow region
			int gradient_pos = (int)((depth_factor - 0.3f) * 100 / 0.4f);
			fdf->color[i] = gradient(mid_shadow, original_color, 100, gradient_pos);
		}
		else
		{
			// Bright region (closest points) - apply subtle darkening
			uint32_t bright_color = original_color;
			
			// Slightly enhance brightness for closest points
			int r = ((bright_color >> 16) & 0xFF);
			int g = ((bright_color >> 8) & 0xFF);
			int b = (bright_color & 0xFF);
			
			// Add slight brightness boost
			r = (r * 110) / 100; if (r > 255) r = 255;
			g = (g * 110) / 100; if (g > 255) g = 255;
			b = (b * 110) / 100; if (b > 255) b = 255;
			
			fdf->color[i] = (r << 16) | (g << 8) | b;
		}
	}
}

// Apply ambient occlusion-like effect based on local height differences
void apply_ambient_shadows(t_app *fdf)
{
	if (!fdf || !fdf->color || !fdf->points)
		return;
	
	for (int y = 1; y < fdf->height - 1; y++)
	{
		for (int x = 1; x < fdf->width - 1; x++)
		{
			int index = y * fdf->width + x;
			float center_z = fdf->points[index];
			
			// Check surrounding points for occlusion
			float occlusion_factor = 0.0f;
			int neighbor_count = 0;
			
			// Check 8 neighbors
			for (int dy = -1; dy <= 1; dy++)
			{
				for (int dx = -1; dx <= 1; dx++)
				{
					if (dx == 0 && dy == 0) continue;
					
					int nx = x + dx;
					int ny = y + dy;
					if (nx >= 0 && nx < fdf->width && ny >= 0 && ny < fdf->height)
					{
						int neighbor_index = ny * fdf->width + nx;
						float neighbor_z = fdf->points[neighbor_index];
						
						// If neighbor is higher, it casts shadow
						if (neighbor_z > center_z)
						{
							occlusion_factor += (neighbor_z - center_z);
						}
						neighbor_count++;
					}
				}
			}
			
			if (neighbor_count > 0)
			{
				occlusion_factor /= neighbor_count;
				
				// Normalize occlusion factor
				float max_occlusion = 20.0f; // Adjust for sensitivity
				if (occlusion_factor > max_occlusion)
					occlusion_factor = max_occlusion;
				
				float shadow_strength = occlusion_factor / max_occlusion;
				
				// Apply shadow to color
				uint32_t original_color = fdf->color[index];
				int r = ((original_color >> 16) & 0xFF);
				int g = ((original_color >> 8) & 0xFF);
				int b = (original_color & 0xFF);
				
				// Darken based on occlusion
				float darken_factor = 1.0f - (shadow_strength * 0.5f);
				r = (int)(r * darken_factor);
				g = (int)(g * darken_factor);
				b = (int)(b * darken_factor);
				
				fdf->color[index] = (r << 16) | (g << 8) | b;
			}
		}
	}
}

// Enhanced shadow system with multiple effects
void apply_shadow_effects(t_app *fdf, bool depth_shadows, bool ambient_shadows)
{
	if (!fdf)
		return;
	
	// Apply depth-based shadows (Z-value fading)
	if (depth_shadows)
		apply_depth_shadow(fdf);
	
	// Apply ambient occlusion-like shadows
	if (ambient_shadows)
		apply_ambient_shadows(fdf);
}

// Toggle different shadow modes
static int g_shadow_mode = 0; // 0=off, 1=depth only, 2=ambient only, 3=both

void toggle_shadow_mode(void)
{
	g_shadow_mode = (g_shadow_mode + 1) % 4;
}

void update_shadow_effects(t_app *fdf)
{
	if (g_shadow_mode == 0)
		return; // No shadows
	
	bool depth = (g_shadow_mode == 1 || g_shadow_mode == 3);
	bool ambient = (g_shadow_mode == 2 || g_shadow_mode == 3);
	
	apply_shadow_effects(fdf, depth, ambient);
}

int get_shadow_mode(void)
{
	return g_shadow_mode;
}
