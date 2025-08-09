/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:28:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 02:12:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

#define TRANSITION_FRAMES 60

// helper to access state
static inline t_transition_state	*tr(t_app *f)
{
	return (&f->transition_state);
}

// Ease-in-out function
static float ease_in_out(float t)
{
	return t * t * (3.0f - 2.0f * t);
}

// Store original grid positions once
static void store_original_positions(t_app *fdf)
{
	t_transition_state	*st;
	int					y;
	int					x;
	int					index;

	st = tr(fdf);
	if (st->initialized)
		return ;
	if (st->original_positions)
		free(st->original_positions);
	st->original_positions = malloc(sizeof(float)
			* fdf->width * fdf->height * 3);
	if (!st->original_positions)
		return ;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			st->original_positions[index * 3 + 0] = (float)x;
			st->original_positions[index * 3 + 1] = (float)y;
			st->original_positions[index * 3 + 2] = fdf->points[index];
			++x;
		}
		++y;
	}
	st->initialized = true;
}

// Get shape position based on shape type
static void get_shape_position(
	t_shape_type shape, t_app *fdf, int x, int y,
	float *ox, float *oy, float *oz)
{
	t_transition_state	*st;
	int					index;
	float				orig_z;

	st = tr(fdf);
	index = y * fdf->width + x;
	if (index >= fdf->width * fdf->height)
	{
		*ox = (float)x;
		*oy = (float)y;
		*oz = 0.0f;
		return ;
	}
	orig_z = st->original_positions[index * 3 + 2];

	switch (shape)
	{
		case SHAPE_ORIGINAL:
			*ox = (float)x;
			*oy = (float)y;
			*oz = orig_z;
			break;
			
		case SHAPE_TORUS:
		{
			float major_r = fminf(fdf->width, fdf->height) / 3.0f;
			float minor_r = major_r / 4.0f;
			float u = (2.0f * M_PI * x) / (float)(fdf->width - 1);
			float v = (2.0f * M_PI * y) / (float)(fdf->height - 1);
			
			*ox = (major_r + minor_r * cosf(v)) * cosf(u);
			*oy = (major_r + minor_r * cosf(v)) * sinf(u);
			*oz = minor_r * sinf(v) + orig_z * 0.05f;
			break;
		}
		
		case SHAPE_SPHERE:
		{
			float radius = fminf(fdf->width, fdf->height) / 3.0f;
			float theta = (2.0f * M_PI * x) / (float)(fdf->width - 1);
			float phi = (M_PI * y) / (float)(fdf->height - 1);
			
			*ox = radius * sinf(phi) * cosf(theta);
			*oy = radius * sinf(phi) * sinf(theta);
			*oz = radius * cosf(phi) + orig_z * 0.05f;
			break;
		}
		
		case SHAPE_CUBE:
		{
			float cube_size = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			*ox = norm_x * cube_size / 2.0f;
			*oy = norm_y * cube_size / 2.0f;
			
			// Simplified cube logic for transitions
			if (fabsf(norm_x) <= 0.8f && fabsf(norm_y) <= 0.8f)
			{
				float dist = sqrtf(norm_x * norm_x + norm_y * norm_y);
				*oz = cube_size / 2.0f * (1.0f - dist * 0.3f) + orig_z * 0.1f;
			}
			else
				*oz = orig_z * 0.1f;
			break;
		}
		
		case SHAPE_PYRAMID:
		{
			float base = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			float dist = fmaxf(fabsf(norm_x), fabsf(norm_y));
			
			*ox = norm_x * base / 2.0f;
			*oy = norm_y * base / 2.0f;
			*oz = (dist <= 1.0f) ? base * (1.0f - dist) + orig_z * 0.05f : orig_z * 0.05f;
			break;
		}
		
		case SHAPE_DNA:
		{
			float dna_radius = fminf(fdf->width, fdf->height) / 6.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			float height_param = norm_y;
			float twist_angle = height_param * 4.0f * M_PI;
			
			// Simplified DNA for transitions
			float phase = (x % 2 == 0) ? 0.0f : M_PI;
			*ox = dna_radius * cosf(twist_angle + phase);
			*oy = height_param * fdf->height * 0.4f;
			*oz = dna_radius * sinf(twist_angle + phase) + orig_z * 0.02f;
			break;
		}
		
		case SHAPE_CHIPS:
		{
			float scale = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			*ox = norm_x * scale;
			*oy = norm_y * scale;
			*oz = 0.3f * (norm_x * norm_x - norm_y * norm_y) * scale + orig_z * 0.1f;
			break;
		}
		
		case SHAPE_WAVE:
		{
			float wave_amplitude = fminf(fdf->width, fdf->height) / 6.0f;
			float base_radius = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			*ox = norm_x * base_radius;
			*oy = norm_y * base_radius;
			
			float wave1 = sinf(norm_x * 3.0f * M_PI) * cosf(norm_y * 3.0f * M_PI);
			*oz = wave_amplitude * wave1 + orig_z * 0.1f;
			break;
		}
		
		case SHAPE_HEART:
		{
			float heart_scale = fminf(fdf->width, fdf->height) / 4.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = -((2.0f * y / (fdf->height - 1)) - 1.0f); // Flip Y
			
			*ox = norm_x * heart_scale;
			*oy = norm_y * heart_scale;
			
			// Simplified heart shape for transitions
			if (norm_y > 0.0f)
			{
				// Upper lobes
				float dist1 = sqrtf((norm_x + 0.5f) * (norm_x + 0.5f) + (norm_y - 0.3f) * (norm_y - 0.3f));
				float dist2 = sqrtf((norm_x - 0.5f) * (norm_x - 0.5f) + (norm_y - 0.3f) * (norm_y - 0.3f));
				if (dist1 < 0.6f || dist2 < 0.6f)
					*oz = heart_scale * 0.3f;
				else
					*oz = 0.0f;
			}
			else
			{
				// Lower point
				float point_factor = 1.0f + norm_y;
				if (point_factor > 0.0f && fabsf(norm_x) < point_factor * 0.8f)
					*oz = heart_scale * 0.2f * point_factor;
				else
					*oz = 0.0f;
			}
			*oz += orig_z * 0.02f;
			break;
		}
		
		case SHAPE_CONE:
		{
			float max_radius = fminf(fdf->width, fdf->height) / 4.0f;
			float angle = ((float)x / fdf->width) * 2.0f * M_PI;
			float height = (float)y - (fdf->height / 2.0f);
			float height_limit = fdf->height * 0.5f;
			
			if (fabsf(height) < height_limit)
			{
				float radius = max_radius * (1.0f - fabsf(height) / height_limit);
				*ox = radius * cosf(angle);
				*oy = height;
				*oz = radius * sinf(angle);
			}
			else
			{
				*ox = 0.0f;
				*oy = height;
				*oz = 0.0f;
			}
			break;
		}
		
		case SHAPE_TUBE:
		{
			float base_radius = fminf(fdf->width, fdf->height) / 4.0f;
			float height_limit = fdf->height * 0.5f;
			
			float angle = ((float)x / fdf->width) * 2.0f * M_PI;
			float radius = base_radius + orig_z * 0.3f;
			float height = (float)y - (fdf->height / 2.0f);
			
			// Check if we're at the top or bottom edge to create caps
			if (fabsf(height) >= height_limit * 0.95f)
			{
				// Create circular caps using 2D grid coordinates
				float center_x = fdf->width / 2.0f;
				float center_y = fdf->height / 2.0f;
				
				// Calculate distance from center of the grid
				float dx = x - center_x;
				float dy = (y < center_y) ? (y - 0) : (y - (fdf->height - 1));
				float grid_radius = sqrtf(dx * dx + dy * dy);
				float max_grid_radius = fdf->width / 2.0f;
				
				// Only create cap if point is within circular boundary
				if (grid_radius <= max_grid_radius)
				{
					float cap_ratio = grid_radius / max_grid_radius;
					float cap_radius = cap_ratio * radius;
					
					*ox = cap_radius * cosf(angle);
					*oy = height;
					*oz = cap_radius * sinf(angle);
				}
				else
				{
					// Points outside circle
					*ox = 0.0f;
					*oy = height;
					*oz = 0.0f;
				}
			}
			else
			{
				// Normal cylinder wall
				*ox = radius * cosf(angle);
				*oy = height;
				*oz = radius * sinf(angle);
			}
			break;
		}
		case SHAPE_COUNT: // added: sentinel handled as original
		default:
			*ox = (float)x;
			*oy = (float)y;
			*oz = orig_z;
			break;
	}
}

// Apply current shape with transformation matrix (for persistent shapes)
static void apply_shape_with_transform(t_app *fdf, t_shape_type shape)
{
	switch (shape)
	{
		case SHAPE_ORIGINAL:
			// Use normal point transformation - matrix will be applied in transform_points()
			break;
		case SHAPE_TORUS:
			apply_torus_transformation(fdf, 0, 0);
			break;
		case SHAPE_SPHERE:
			// For sphere, apply shape transformation
			for (int y = 0; y < fdf->height; y++)
			{
				for (int x = 0; x < fdf->width; x++)
				{
					int index = y * fdf->width + x;
					float shape_x, shape_y, shape_z;
					get_shape_position(SHAPE_SPHERE, fdf, x, y, &shape_x, &shape_y, &shape_z);
					
					float sp[4] = {shape_x, shape_y, shape_z, 1};
					float *dp = (float *)&fdf->transformed_points[index];
					matrix4_dot_product(fdf->trans_stack.combined, sp, dp);
				}
			}
			break;
		case SHAPE_CUBE:
			apply_cube_transformation(fdf);
			break;
		case SHAPE_PYRAMID:
			apply_pyramid_transformation(fdf);
			break;
		case SHAPE_DNA:
			apply_dna_transformation(fdf);
			break;
		case SHAPE_CHIPS:
			apply_chips_transformation(fdf);
			break;
		case SHAPE_WAVE:
			apply_wave_transformation(fdf);
			break;
		case SHAPE_HEART:
			apply_heart_transformation(fdf);
			break;
		case SHAPE_CONE:
			apply_cone_transformation(fdf);
			break;
		case SHAPE_TUBE:
			apply_tube_transformation(fdf);
			break;
		case SHAPE_COUNT: // added: sentinel -> no-op
		default:
			break;
	}
}

void	transition_update(t_app *fdf)
{
	t_transition_state	*st;
	int					y;
	int					x;

	st = tr(fdf);
	if (!st->active && st->current_shape == SHAPE_ORIGINAL)
		return ;
	store_original_positions(fdf);
	if (!st->original_positions)
		return ;
	if (st->active)
	{
		float	progress;
		float	smooth_t;

		progress = (float)st->frame / st->max_frames;
		smooth_t = ease_in_out(progress);
		y = 0;
		while (y < fdf->height)
		{
			x = 0;
			while (x < fdf->width)
			{
				int		index = y * fdf->width + x;
				float	cx, cy, cz, tx, ty, tz, fx, fy, fz;
				float	sp[4];
				float	*dp;

				get_shape_position(st->current_shape, fdf, x, y, &cx, &cy, &cz);
				get_shape_position(st->target_shape, fdf, x, y, &tx, &ty, &tz);
				fx = cx + (tx - cx) * smooth_t;
				fy = cy + (ty - cy) * smooth_t;
				fz = cz + (tz - cz) * smooth_t;
				sp[0] = fx;
				sp[1] = fy;
				sp[2] = fz;
				sp[3] = 1.0f;
				dp = (float *)&fdf->transformed_points[index];
				matrix4_dot_product(fdf->trans_stack.combined, sp, dp);
				++x;
			}
			++y;
		}
		++st->frame;
		if (st->frame >= st->max_frames)
		{
			st->active = false;
			st->frame = 0;
			st->current_shape = st->target_shape;
		}
	}
	else if (st->current_shape != SHAPE_ORIGINAL)
		apply_shape_with_transform(fdf, st->current_shape);
}

void	transition_start_torus(bool to_torus)
{
	(void)to_torus;
	// kept for compatibility – now handled by transition_start_object_effects if needed
}

void	transition_start_shape_cycle(t_app *fdf)
{
	t_transition_state	*st;

	st = tr(fdf);
	st->active = true;
	st->frame = 0;
	st->target_shape = (st->current_shape + 1) % SHAPE_COUNT;
	if (st->target_shape == SHAPE_ORIGINAL)
		st->target_shape = (st->current_shape + 2) % SHAPE_COUNT;
}

bool	transition_is_active(void)
{
	// legacy fallback (original global removed) – caller should pass app now
	return (false);
}

bool	transition_app_is_active(t_app *fdf)
{
	t_transition_state	*st;

	st = tr(fdf);
	return (st->active || st->current_shape != SHAPE_ORIGINAL);
}

void	transition_cleanup(t_app *fdf)
{
	t_transition_state	*st;

	st = tr(fdf);
	if (st->original_positions)
	{
		free(st->original_positions);
		st->original_positions = NULL;
	}
	st->initialized = false;
	st->active = false;
	st->frame = 0;
	st->current_shape = SHAPE_ORIGINAL;
	st->target_shape = SHAPE_ORIGINAL;
	st->max_frames = TRANSITION_FRAMES;
}
