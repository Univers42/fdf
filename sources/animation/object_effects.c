#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "fdf.h"

#define OBJECT_EFFECT_COUNT 10
#define WAVE_FREQUENCY 0.1f
#define PULSE_SPEED 0.05f
#define TWIST_RATE 0.02f

typedef enum e_object_effect_type {
	OBJ_EFFECT_NONE = 0,
	OBJ_EFFECT_VERTEX_WAVE = 1,
	OBJ_EFFECT_GEOMETRIC_PULSE = 2,
	OBJ_EFFECT_VERTEX_EXPLOSION = 3,
	OBJ_EFFECT_SPIRAL_TWIST = 4,
	OBJ_EFFECT_DEPTH_DISTORTION = 5,
	OBJ_EFFECT_VERTEX_MAGNET = 6,
	OBJ_EFFECT_GEOMETRIC_FOLD = 7,
	OBJ_EFFECT_HEIGHT_OSCILLATION = 8,
	OBJ_EFFECT_VERTEX_SCATTER = 9
} t_object_effect_type;

typedef struct s_object_effects_system {
	t_object_effect_type	current_effect;
	bool					active;
	float					time_accumulator;
	float					intensity;
	bool					initialized;
	float					*original_points;
	int						total_points;
} t_object_effects_system;

static t_object_effects_system g_obj_effects = {OBJ_EFFECT_NONE, false, 0.0f, 1.0f, false, NULL, 0};

// Store original point positions
static void store_original_object_points(t_app *fdf)
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
}

// Apply vertex wave effect - creates rippling waves across the surface
static void apply_vertex_wave_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float wave_amplitude = 20.0f * g_obj_effects.intensity;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Normalize coordinates
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create multiple wave patterns
			float wave1 = sinf((norm_x * 8.0f + g_obj_effects.time_accumulator) * M_PI);
			float wave2 = sinf((norm_y * 6.0f + g_obj_effects.time_accumulator * 0.7f) * M_PI);
			float wave3 = sinf(((norm_x + norm_y) * 5.0f + g_obj_effects.time_accumulator * 1.2f) * M_PI);
			
			// Combine waves
			float wave_effect = (wave1 + wave2 + wave3) / 3.0f;
			
			// Apply to Z coordinate
			fdf->points[index] = g_obj_effects.original_points[index] + wave_effect * wave_amplitude;
		}
	}
}

// Apply geometric pulse effect - makes the entire object pulse in size
static void apply_geometric_pulse_effect(t_app *fdf)
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

// Apply vertex explosion effect - vertices move away from center
static void apply_vertex_explosion_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float explosion_strength = 50.0f * g_obj_effects.intensity;
	float center_x = fdf->width / 2.0f;
	float center_y = fdf->height / 2.0f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Calculate distance from center
			float dx = x - center_x;
			float dy = y - center_y;
			float distance = sqrtf(dx * dx + dy * dy);
			
			// Normalize distance
			float max_distance = sqrtf(center_x * center_x + center_y * center_y);
			float norm_distance = distance / max_distance;
			
			// Create explosion effect
			float explosion_factor = sinf(g_obj_effects.time_accumulator * 2.0f) * norm_distance;
			
			fdf->points[index] = g_obj_effects.original_points[index] + explosion_factor * explosion_strength;
		}
	}
}

// Apply spiral twist effect - twists the geometry
static void apply_spiral_twist_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float twist_strength = 2.0f * g_obj_effects.intensity;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Calculate twist based on distance from center and time
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			float dx = x - center_x;
			float dy = y - center_y;
			float distance = sqrtf(dx * dx + dy * dy);
			
			// Create spiral twist
			float twist_angle = distance * 0.1f + g_obj_effects.time_accumulator * twist_strength;
			float twist_effect = sinf(twist_angle) * 30.0f;
			
			fdf->points[index] = g_obj_effects.original_points[index] + twist_effect;
		}
	}
}

// Apply depth distortion effect - warps depth based on position
static void apply_depth_distortion_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Normalize coordinates
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create depth distortion pattern
			float distortion = sinf((norm_x + norm_y + g_obj_effects.time_accumulator) * M_PI * 4.0f);
			distortion *= g_obj_effects.intensity * 25.0f;
			
			fdf->points[index] = g_obj_effects.original_points[index] + distortion;
		}
	}
}

// Apply vertex magnet effect - attracts vertices to moving points
static void apply_vertex_magnet_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	// Moving magnet positions
	float magnet1_x = (sinf(g_obj_effects.time_accumulator * 0.8f) + 1.0f) * fdf->width * 0.5f;
	float magnet1_y = (cosf(g_obj_effects.time_accumulator * 0.6f) + 1.0f) * fdf->height * 0.5f;
	
	float magnet2_x = (sinf(g_obj_effects.time_accumulator * 1.2f + M_PI) + 1.0f) * fdf->width * 0.5f;
	float magnet2_y = (cosf(g_obj_effects.time_accumulator * 0.9f + M_PI) + 1.0f) * fdf->height * 0.5f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Calculate distances to magnets
			float dx1 = x - magnet1_x;
			float dy1 = y - magnet1_y;
			float dist1 = sqrtf(dx1 * dx1 + dy1 * dy1) + 1.0f; // +1 to avoid division by zero
			
			float dx2 = x - magnet2_x;
			float dy2 = y - magnet2_y;
			float dist2 = sqrtf(dx2 * dx2 + dy2 * dy2) + 1.0f;
			
			// Calculate magnetic forces
			float force1 = 500.0f / (dist1 * dist1);
			float force2 = -300.0f / (dist2 * dist2); // Repelling magnet
			
			float total_force = (force1 + force2) * g_obj_effects.intensity;
			
			fdf->points[index] = g_obj_effects.original_points[index] + total_force;
		}
	}
}

// Apply geometric fold effect - creates folding patterns
static void apply_geometric_fold_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float fold_frequency = 4.0f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create folding pattern
			float fold1 = fabs(sinf((norm_x * fold_frequency + g_obj_effects.time_accumulator) * M_PI));
			float fold2 = fabs(sinf((norm_y * fold_frequency + g_obj_effects.time_accumulator * 0.7f) * M_PI));
			
			float fold_effect = (fold1 + fold2) * 20.0f * g_obj_effects.intensity;
			
			fdf->points[index] = g_obj_effects.original_points[index] + fold_effect;
		}
	}
}

// Apply height oscillation effect - oscillates based on original height
static void apply_height_oscillation_effect(t_app *fdf)
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

// Apply vertex scatter effect - randomly displaces vertices
static void apply_vertex_scatter_effect(t_app *fdf)
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
		for (int x = 0; x < fdf->width; x++) // Fix: close the loop properly
		{
			int index = y * fdf->width + x;
			
			// Create smooth random displacement
			float noise = sinf(g_obj_effects.time_accumulator * 2.0f + noise_offsets[index] * M_PI * 2.0f);
			float scatter = noise * 25.0f * g_obj_effects.intensity;
			
			fdf->points[index] = g_obj_effects.original_points[index] + scatter;
		}
	}
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
		printf("Object Effect: %s (intensity: %.1f)\n", 
			   effect_names[g_obj_effects.current_effect], g_obj_effects.intensity);
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

// Cleanup object effects system
void object_effects_cleanup(void)
{
	if (g_obj_effects.original_points)
	{
		free(g_obj_effects.original_points);
		g_obj_effects.original_points = NULL;
	}
	
	g_obj_effects.initialized = false;
	g_obj_effects.current_effect = OBJ_EFFECT_NONE;
	g_obj_effects.time_accumulator = 0.0f;
	g_obj_effects.intensity = 1.0f;
	
	printf("Object effects system cleaned up\n");
}

// Set object effect intensity
void set_object_effect_intensity(float intensity)
{
	g_obj_effects.intensity = fmaxf(0.1f, fminf(2.0f, intensity));
}
