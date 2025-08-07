/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_integration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fdf.h"

typedef struct s_trackball_state {
	float current_quat[4];
	float last_quat[4];
	bool active;
	bool initialized;
	int last_mouse_x;
	int last_mouse_y;
} t_trackball_state;

typedef struct s_trackball_shape_state {
	float current_rotation[4];
	float rotation_matrix[16];
	bool is_active;
} t_trackball_shape_state;

// Global state for shape-specific trackball and auto-rotation
t_trackball_shape_state g_trackball_state = {
	.current_rotation = {0.0f, 0.0f, 0.0f, 1.0f},
	.rotation_matrix = {1.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 1.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 1.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 1.0f},
	.is_active = false
};

static t_trackball_state g_trackball = {0};

// Helper: multiply a 4x4 matrix with a 3D point (homogeneous)
static void matrix4_apply_to_point(const float *m, float *x, float *y, float *z)
{
	float v[4] = {*x, *y, *z, 1.0f};
	float out[4] = {0};
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			out[i] += m[i * 4 + j] * v[j];
	*x = out[0];
	*y = out[1];
	*z = out[2];
}

void init_trackball_system(void)
{
	// Initialize identity quaternion
	g_trackball.current_quat[0] = 0.0f;
	g_trackball.current_quat[1] = 0.0f;
	g_trackball.current_quat[2] = 0.0f;
	g_trackball.current_quat[3] = 1.0f;
	
	g_trackball.last_quat[0] = 0.0f;
	g_trackball.last_quat[1] = 0.0f;
	g_trackball.last_quat[2] = 0.0f;
	g_trackball.last_quat[3] = 1.0f;
	
	g_trackball.active = false;
	g_trackball.initialized = true;
}

void trackball_start_rotation(int mouse_x, int mouse_y)
{
	if (!g_trackball.initialized)
		init_trackball_system();
	
	g_trackball.active = true;
	g_trackball.last_mouse_x = mouse_x;
	g_trackball.last_mouse_y = mouse_y;
	
	// Store current rotation as base
	for (int i = 0; i < 4; i++)
		g_trackball.last_quat[i] = g_trackball.current_quat[i];
}

void trackball_update_rotation(int mouse_x, int mouse_y)
{
	if (!g_trackball.active || !g_trackball.initialized)
		return;
	
	// Convert mouse coordinates to normalized trackball coordinates [-1, 1]
	float p1x = (2.0f * g_trackball.last_mouse_x - WIN_WIDTH) / WIN_WIDTH;
	float p1y = (WIN_HEIGHT - 2.0f * g_trackball.last_mouse_y) / WIN_HEIGHT;
	float p2x = (2.0f * mouse_x - WIN_WIDTH) / WIN_WIDTH;
	float p2y = (WIN_HEIGHT - 2.0f * mouse_y) / WIN_HEIGHT;
	
	// Calculate rotation quaternion
	float rotation_quat[4];
	trackball_rotate(rotation_quat, p1x, p1y, p2x, p2y);
	
	// Combine with previous rotation
	add_quats(g_trackball.last_quat, rotation_quat, g_trackball.current_quat);
}

void trackball_end_rotation(void)
{
	g_trackball.active = false;
}

// Apply trackball rotation to the transformation stack
void apply_trackball_to_transform_stack(t_app *fdf)
{
	if (!g_trackball.initialized || !transition_is_active())
		return;
	
	// Convert quaternion to 4x4 matrix
	float rotation_matrix[16];
	quaternion_to_matrix4(g_trackball.current_quat, rotation_matrix);
	
	// Apply trackball rotation by modifying the transformation matrix directly
	float temp_matrix[16];
	matrix4_multiply(fdf->trans_stack.combined, rotation_matrix, temp_matrix);
	
	// Copy result back
	for (int i = 0; i < 16; i++)
		fdf->trans_stack.combined[i] = temp_matrix[i];
}

// Apply automatic trackball rotation for shapes (space bar)
void apply_auto_trackball_rotation(t_app *fdf, float rotation_speed)
{
	if (!transition_is_active())
		return;

	// Rotate all transformed points around the Y axis (left-to-right)
	float angle = rotation_speed;
	float cos_a = cosf(angle);
	float sin_a = sinf(angle);

	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int idx = y * fdf->width + x;
			float px = fdf->transformed_points[idx].x;
			float py = fdf->transformed_points[idx].y;
			float pz = fdf->transformed_points[idx].z;

			// Rotate around Y axis (left-right)
			float rx = px * cos_a + pz * sin_a;
			float rz = -px * sin_a + pz * cos_a;

			fdf->transformed_points[idx].x = rx;
			fdf->transformed_points[idx].y = py;
			fdf->transformed_points[idx].z = rz;
		}
	}
}

// Enhanced trackball application specifically for shapes
void apply_trackball_to_shape_points(t_app *fdf)
{
	// Only apply manual trackball rotations when user is actively rotating
	if (!g_trackball_state.is_active)
		return;

	if (transition_is_active())
	{
		// Compute centroid of the shape
		float cx = 0.0f, cy = 0.0f, cz = 0.0f;
		int total_points = fdf->width * fdf->height;
		
		for (int i = 0; i < total_points; i++)
		{
			cx += fdf->transformed_points[i].x;
			cy += fdf->transformed_points[i].y;
			cz += fdf->transformed_points[i].z;
		}
		cx /= total_points;
		cy /= total_points;
		cz /= total_points;

		for (int y = 0; y < fdf->height; y++)
		{
			for (int x = 0; x < fdf->width; x++)
			{
				int idx = y * fdf->width + x;
				float sx = fdf->transformed_points[idx].x - cx;
				float sy = fdf->transformed_points[idx].y - cy;
				float sz = fdf->transformed_points[idx].z - cz;

				// Rotate around centroid
				matrix4_apply_to_point(g_trackball_state.rotation_matrix, &sx, &sy, &sz);

				// Move back to centroid
				fdf->transformed_points[idx].x = sx + cx;
				fdf->transformed_points[idx].y = sy + cy;
				fdf->transformed_points[idx].z = sz + cz;
			}
		}
		
		// Reset the trackball state after applying to prevent accumulation
		g_trackball_state.is_active = false;
	}
}

bool is_trackball_active(void)
{
	return g_trackball.active;
}

void reset_trackball_rotation(void)
{
	init_trackball_system();
	
	// Reset the shape trackball state
	g_trackball_state.current_rotation[0] = 0.0f;
	g_trackball_state.current_rotation[1] = 0.0f;
	g_trackball_state.current_rotation[2] = 0.0f;
	g_trackball_state.current_rotation[3] = 1.0f;
	
	// Reset rotation matrix to identity
	for (int i = 0; i < 16; i++)
		g_trackball_state.rotation_matrix[i] = 0.0f;
	g_trackball_state.rotation_matrix[0] = 1.0f;
	g_trackball_state.rotation_matrix[5] = 1.0f;
	g_trackball_state.rotation_matrix[10] = 1.0f;
	g_trackball_state.rotation_matrix[15] = 1.0f;
	
	g_trackball_state.is_active = false;
}
