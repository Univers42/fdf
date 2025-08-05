/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_effect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:28:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 01:35:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PARALLAX_LAYERS 3
#define GRID_SIZE 50.0f
#define PARALLAX_SPEED 0.02f
#define PARALLAX_PARTICLES 50
#define PARALLAX_GRID_BASE 100
#define PARALLAX_DEPTH_SCALE 0.7f
#define PARALLAX_FADE_FACTOR 40
#define PARALLAX_MIN_ALPHA 30
#define PARALLAX_BOUNCE_DAMPING 0.95f
#define PARALLAX_PERSPECTIVE_SCALE 0.1f
#define TRAIL_ALPHA 0.1f

typedef struct s_parallax_layer {
	float	offset_x;
	float	offset_y;
	float	depth;
	float	speed_factor;
	uint32_t color;
	bool	visible;
	float	bounce_offset_x;
	float	bounce_offset_y;
	int		bounce_dir_x;
	int		bounce_dir_y;
} t_parallax_layer;

typedef struct s_parallax_system {
	t_parallax_layer	layers[PARALLAX_LAYERS];
	bool				active;
	float				camera_x;
	float				camera_y;
	bool				trail_active;
	float				particle_positions[PARALLAX_PARTICLES][2];
	bool				particles_initialized;
	float				particle_phase;
} t_parallax_system;

static t_parallax_system g_parallax = {0};

// Calculate responsive grid size based on screen dimensions
static int get_responsive_grid_size(int layer)
{
	float screen_factor = (float)(WIN_WIDTH + WIN_HEIGHT) / (1920.0f + 1080.0f);
	int base_size = (int)(PARALLAX_GRID_BASE * screen_factor);
	return base_size * (layer + 1);
}

// Initialize the parallax system with bouncing and particles
void init_parallax_system(void)
{
	g_parallax.active = false;
	g_parallax.camera_x = 0.0f;
	g_parallax.camera_y = 0.0f;
	g_parallax.trail_active = false;
	g_parallax.particles_initialized = false;
	g_parallax.particle_phase = 0.0f;
	
	// Initialize each layer with bouncing properties
	for (int i = 0; i < PARALLAX_LAYERS; i++)
	{
		g_parallax.layers[i].depth = -500.0f * (i + 1);
		g_parallax.layers[i].speed_factor = 0.2f + (i * 0.3f);
		g_parallax.layers[i].visible = true;
		g_parallax.layers[i].offset_x = 0.0f;
		g_parallax.layers[i].offset_y = 0.0f;
		g_parallax.layers[i].bounce_offset_x = 0.0f;
		g_parallax.layers[i].bounce_offset_y = 0.0f;
		g_parallax.layers[i].bounce_dir_x = 1;
		g_parallax.layers[i].bounce_dir_y = 1;
		
		// Layer colors with fade effect
		int layer_alpha = 0xFF - (i * PARALLAX_FADE_FACTOR);
		if (layer_alpha < PARALLAX_MIN_ALPHA)
			layer_alpha = PARALLAX_MIN_ALPHA;
		int base_color = 0x2A + i * 0x10;
		g_parallax.layers[i].color = (layer_alpha << 24) | (base_color << 16) | (base_color << 8) | base_color;
	}
	
	// Initialize particle positions
	for (int i = 0; i < PARALLAX_PARTICLES; i++)
	{
		g_parallax.particle_positions[i][0] = (float)((i * 73 + 17) % WIN_WIDTH);
		g_parallax.particle_positions[i][1] = (float)((i * 137 + 23) % WIN_HEIGHT);
	}
	g_parallax.particles_initialized = true;
}

// Update camera position for parallax effect with bouncing
void update_parallax_camera(t_app *fdf)
{
	if (!g_parallax.active)
		return;
	
	// Use rotation and translation values for camera tracking
	static float prev_rx = 0.0f, prev_ry = 0.0f;
	static float prev_tx = 0.0f, prev_ty = 0.0f;

	float dx = (fdf->transformation_stack.rx - prev_rx) * 50.0f;
	float dy = (fdf->transformation_stack.ry - prev_ry) * 50.0f;
	float dt_x = (fdf->transformation_stack.tx - prev_tx) * 10.0f;
	float dt_y = (fdf->transformation_stack.ty - prev_ty) * 10.0f;
	
	g_parallax.camera_x += dx + dt_x;
	g_parallax.camera_y += dy + dt_y;
	
	// Update previous values
	prev_rx = fdf->transformation_stack.rx;
	prev_ry = fdf->transformation_stack.ry;
	prev_tx = fdf->transformation_stack.tx;
	prev_ty = fdf->transformation_stack.ty;
	
	// Update layer offsets with bouncing physics
	float screen_scale = (float)WIN_WIDTH / 1920.0f;
	
	for (int i = 0; i < PARALLAX_LAYERS; i++)
	{
		t_parallax_layer *layer = &g_parallax.layers[i];
		float depth_factor = powf(PARALLAX_DEPTH_SCALE, i);
		
		// Get responsive grid size for bounce limits
		int layer_grid_size = get_responsive_grid_size(i);
		float bounce_limit = layer_grid_size * 2.0f * screen_scale;
		
		// Calculate movement deltas
		float delta_x = g_parallax.camera_x * PARALLAX_SPEED * depth_factor;
		float delta_y = g_parallax.camera_y * PARALLAX_SPEED * depth_factor;
		
		// Update bounce positions with direction
		layer->bounce_offset_x += delta_x * layer->bounce_dir_x;
		layer->bounce_offset_y += delta_y * layer->bounce_dir_y;
		
		// X-axis bouncing with damping
		if (fabsf(layer->bounce_offset_x) > bounce_limit)
		{
			layer->bounce_dir_x *= -1;
			layer->bounce_offset_x = bounce_limit * layer->bounce_dir_x;
			layer->bounce_offset_x *= PARALLAX_BOUNCE_DAMPING;
		}
		
		// Y-axis bouncing with damping
		if (fabsf(layer->bounce_offset_y) > bounce_limit)
		{
			layer->bounce_dir_y *= -1;
			layer->bounce_offset_y = bounce_limit * layer->bounce_dir_y;
			layer->bounce_offset_y *= PARALLAX_BOUNCE_DAMPING;
		}
		
		// Apply smooth sine wave modulation for organic feel
		float wave_amplitude = 5.0f * screen_scale;
		layer->offset_x = layer->bounce_offset_x + sinf(layer->bounce_offset_x * 0.01f) * wave_amplitude;
		layer->offset_y = layer->bounce_offset_y + sinf(layer->bounce_offset_y * 0.01f) * wave_amplitude;
	}
}

// Draw thick line for enhanced visual effects
static void draw_thick_line(t_app *fdf, int x1, int y1, int x2, int y2, uint32_t color, float thickness)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	if (thickness <= 1.0f)
	{
		// Simple line drawing for thickness 1
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int x = x1, y = y1;
		int x_inc = (x1 < x2) ? 1 : -1;
		int y_inc = (y1 < y2) ? 1 : -1;
		int error = dx - dy;
		
		while (1)
		{
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				screen[y * WIN_WIDTH + x] = color;
			
			if (x == x2 && y == y2) break;
			
			int e2 = 2 * error;
			if (e2 > -dy) { error -= dy; x += x_inc; }
			if (e2 < dx) { error += dx; y += y_inc; }
		}
		return;
	}
	
	// Draw multiple parallel lines for thickness
	float dx = x2 - x1;
	float dy = y2 - y1;
	float len = sqrtf(dx * dx + dy * dy);
	
	if (len > 0)
	{
		float px = -dy / len;  // Perpendicular vector
		float py = dx / len;
		
		for (int i = 0; i < (int)thickness; i++)
		{
			float offset = i - thickness / 2.0f;
			int offset_x1 = x1 + (int)(px * offset);
			int offset_y1 = y1 + (int)(py * offset);
			int offset_x2 = x2 + (int)(px * offset);
			int offset_y2 = y2 + (int)(py * offset);
			
			draw_thick_line(fdf, offset_x1, offset_y1, offset_x2, offset_y2, color, 1.0f);
		}
	}
}

// Draw a single responsive grid layer
static void draw_grid_layer(t_app *fdf, t_parallax_layer *layer, int layer_index)
{
	if (!layer->visible)
		return;
	
	int layer_grid_size = get_responsive_grid_size(layer_index);
	int margin = layer_grid_size * 2;
	
	// Calculate starting positions with screen-aware margins
	int start_x = (int)layer->offset_x - margin;
	int start_y = (int)layer->offset_y - margin;
	
	// Draw vertical lines
	for (int x = start_x; x < WIN_WIDTH + margin; x += layer_grid_size)
	{
		int line_x = x;
		
		// Add perspective effect for background layers
		if (layer_index > 0)
		{
			float perspective_scale = 1.0f - (layer_index * PARALLAX_PERSPECTIVE_SCALE);
			line_x = (int)((line_x - WIN_WIDTH/2) * perspective_scale + WIN_WIDTH/2);
		}
		
		if (line_x >= -margin && line_x < WIN_WIDTH + margin)
		{
			float thickness = 1.0f + layer_index * 0.5f;  // Thicker for background layers
			draw_thick_line(fdf, line_x, 0, line_x, WIN_HEIGHT, layer->color, thickness);
		}
	}
	
	// Draw horizontal lines
	for (int y = start_y; y < WIN_HEIGHT + margin; y += layer_grid_size)
	{
		int line_y = y;
		
		// Add perspective effect for background layers
		if (layer_index > 0)
		{
			float perspective_scale = 1.0f - (layer_index * PARALLAX_PERSPECTIVE_SCALE);
			line_y = (int)((line_y - WIN_HEIGHT/2) * perspective_scale + WIN_HEIGHT/2);
		}
		
		if (line_y >= -margin && line_y < WIN_HEIGHT + margin)
		{
			float thickness = 1.0f + layer_index * 0.5f;  // Thicker for background layers
			draw_thick_line(fdf, 0, line_y, WIN_WIDTH, line_y, layer->color, thickness);
		}
	}
}

// Draw animated particles for extra depth
static void draw_parallax_particles(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	g_parallax.particle_phase += 0.02f;
	
	for (int i = 0; i < PARALLAX_PARTICLES; i++)
	{
		// Smooth bouncing motion with different speeds per particle
		float particle_speed = 0.5f + (i % 3) * 0.3f;
		
		// Screen-aware particle movement
		float move_range_x = WIN_WIDTH * 0.45f;
		float move_range_y = WIN_HEIGHT * 0.45f;
		
		float px = WIN_WIDTH/2 + sinf(g_parallax.particle_phase * particle_speed + i) * move_range_x;
		float py = WIN_HEIGHT/2 + cosf(g_parallax.particle_phase * particle_speed * 0.7f + i) * move_range_y;
		
		// Add offset based on parallax movement
		px += g_parallax.layers[0].offset_x * 0.2f;
		py += g_parallax.layers[0].offset_y * 0.2f;
		
		// Vary particle color and size based on "depth"
		int depth = i % 3;
		uint32_t particle_color = 0x404040 + (depth * 0x202020);
		
		// Responsive particle size
		int particle_size = 1 + depth;
		if (WIN_WIDTH > 2560)  // 4K or higher
			particle_size += 1;
		
		// Draw particle with size
		for (int dy = 0; dy < particle_size; dy++)
		{
			for (int dx = 0; dx < particle_size; dx++)
			{
				int x = (int)px + dx;
				int y = (int)py + dy;
				
				if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
					screen[y * WIN_WIDTH + x] = particle_color;
			}
		}
	}
}

// Apply trail/ghost effect by blending with previous frame
static void apply_trail_effect(t_app *fdf)
{
	if (!g_parallax.trail_active)
		return;
		
	uint32_t *buffer = (uint32_t *)fdf->renderer.data;
	
	// Blend current frame with background to create fade effect
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int pixel = y * WIN_WIDTH + x;
			uint32_t color = buffer[pixel];
			
			// Extract RGB
			int r = (color >> 16) & 0xFF;
			int g = (color >> 8) & 0xFF;
			int b = color & 0xFF;
			
			// Blend with background (fade effect)
			r = (int)(r * (1.0f - TRAIL_ALPHA));
			g = (int)(g * (1.0f - TRAIL_ALPHA));
			b = (int)(b * (1.0f - TRAIL_ALPHA));
			
			uint32_t new_color = (0xFF << 24) | (r << 16) | (g << 8) | b;
			buffer[pixel] = new_color;
		}
	}
}

// Render the complete parallax effect
void render_parallax_effect(t_app *fdf)
{
	if (!g_parallax.active)
		return;
	
	// Apply trail effect first
	apply_trail_effect(fdf);
	
	// Update camera movement
	update_parallax_camera(fdf);
	
	// Draw layers from back to front (far to near)
	for (int i = PARALLAX_LAYERS - 1; i >= 0; i--)
	{
		draw_grid_layer(fdf, &g_parallax.layers[i], i);
	}
	
	// Draw animated particles for extra depth
	draw_parallax_particles(fdf);
}

// Toggle parallax effect
void toggle_parallax_effect(void)
{
	g_parallax.active = !g_parallax.active;
	
	if (g_parallax.active)
	{
		init_parallax_system();
		printf("PARALLAX: Enhanced bouncing grid with particles enabled!\n");
	}
	else
	{
		printf("PARALLAX: Enhanced effects disabled\n");
	}
}

// Check if parallax is active
bool is_parallax_active(void)
{
	return g_parallax.active;
}

// Enhanced animation with more dynamic effects
void animate_parallax_grid(void)
{
	if (!g_parallax.active)
		return;
	
	// Toggle trail effect periodically for visual variety
	static int trail_counter = 0;
	trail_counter++;
	if (trail_counter > 300)  // Every 5 seconds at 60fps
	{
		g_parallax.trail_active = !g_parallax.trail_active;
		trail_counter = 0;
		printf("Trail effect %s\n", g_parallax.trail_active ? "enabled" : "disabled");
	}
	
	// Dynamic color shifting for layers
	static float color_phase = 0.0f;
	color_phase += 0.01f;
	
	for (int i = 0; i < PARALLAX_LAYERS; i++)
	{
		int layer_alpha = 0xFF - (i * PARALLAX_FADE_FACTOR);
		if (layer_alpha < PARALLAX_MIN_ALPHA)
			layer_alpha = PARALLAX_MIN_ALPHA;
		
		// Add subtle color cycling
		int base_color = 0x2A + i * 0x10;
		int color_shift = (int)(sinf(color_phase + i) * 10);
		base_color = fmaxf(0, fminf(255, base_color + color_shift));
		
		g_parallax.layers[i].color = (layer_alpha << 24) | (base_color << 16) | (base_color << 8) | base_color;
	}
}
