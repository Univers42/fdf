#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


t_object_effects_system g_obj_effects = {OBJ_EFFECT_NONE, false, 0.0f, 1.0f, false, NULL, 0};

// Store original point positions
void store_original_object_points(t_app *fdf)
{
	if (g_obj_effects.initialized)
		return;
	
	g_obj_effects.total_points = fdf->width * fdf->height;
	
	if (g_obj_effects.original_points)
		free(g_obj_effects.original_points);
	
	g_obj_effects.original_points = malloc(sizeof(float) * g_obj_effects.total_points);
	if (!g_obj_effects.original_points)
		return;
	
	// Store original Z values
	for (int i = 0; i < g_obj_effects.total_points; i++)
		g_obj_effects.original_points[i] = fdf->points[i];
	
	g_obj_effects.initialized = true;
	printf("Stored %d original points\n", g_obj_effects.total_points);
}

// Main object effects update function
void object_effects_update(t_app *fdf)
{
	if (g_obj_effects.current_effect == OBJ_EFFECT_NONE)
		return;
	
	store_original_object_points(fdf);
	
	if (!g_obj_effects.original_points)
		return;
	
	// Update time
	g_obj_effects.time_accumulator += WAVE_FREQUENCY;
	
	// Apply current effect
	const char *effect_names[] = {
		"None", "Vertex Wave", "Geometric Pulse", "Vertex Explosion", "Spiral Twist",
		"Depth Distortion", "Vertex Magnet", "Geometric Fold", "Height Oscillation", "Vertex Scatter"
	};
	
	switch (g_obj_effects.current_effect)
	{
		case OBJ_EFFECT_NONE:
			break;
		case OBJ_EFFECT_VERTEX_WAVE:
			apply_vertex_wave_effect(fdf);
			break;
		case OBJ_EFFECT_GEOMETRIC_PULSE:
			apply_geometric_pulse_effect(fdf);
			break;
		case OBJ_EFFECT_VERTEX_EXPLOSION:
			apply_vertex_explosion_effect(fdf);
			break;
		case OBJ_EFFECT_SPIRAL_TWIST:
			apply_spiral_twist_effect(fdf);
			break;
		case OBJ_EFFECT_DEPTH_DISTORTION:
			apply_depth_distortion_effect(fdf);
			break;
		case OBJ_EFFECT_VERTEX_MAGNET:
			apply_vertex_magnet_effect(fdf);
			break;
		case OBJ_EFFECT_GEOMETRIC_FOLD:
			apply_geometric_fold_effect(fdf);
			break;
		case OBJ_EFFECT_HEIGHT_OSCILLATION:
			apply_height_oscillation_effect(fdf);
			break;
		case OBJ_EFFECT_VERTEX_SCATTER:
			apply_vertex_scatter_effect(fdf);
			break;
	}
	
	// Debug output occasionally
	static int debug_counter = 0;
	if (++debug_counter % 300 == 0) // Every 5 seconds at 60fps
	{
		printf("Object Effect: %s (intensity: %.1f) - modifying %d points\n", 
			effect_names[g_obj_effects.current_effect], g_obj_effects.intensity, g_obj_effects.total_points);
	}
}

// Start object effect transition (replaces particle effects cycling)
void transition_start_object_effects(bool to_effects)
{
	(void)to_effects; // Unused parameter
	
	// Cycle through object effect types
	t_object_effect_type next_effect = (g_obj_effects.current_effect + 1) % OBJECT_EFFECT_COUNT;
	
	g_obj_effects.current_effect = next_effect;
	g_obj_effects.time_accumulator = 0.0f;
	
	const char *effect_names[] = {
		"None", "Vertex Wave", "Geometric Pulse", "Vertex Explosion", "Spiral Twist",
		"Depth Distortion", "Vertex Magnet", "Geometric Fold", "Height Oscillation", "Vertex Scatter"
	};
	
	printf("Object effects transitioning to: %s\n", effect_names[next_effect]);
}

// Check if object effects are active
bool object_effects_is_active(void)
{
	return g_obj_effects.current_effect != OBJ_EFFECT_NONE;
}


// Set object effect intensity
void set_object_effect_intensity(float intensity)
{
	g_obj_effects.intensity = fmaxf(0.1f, fminf(2.0f, intensity));
}