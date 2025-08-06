#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEXTURE_COUNT 12

typedef enum e_texture_type {
	TEXTURE_NONE = 0,
	TEXTURE_CHECKERBOARD = 1,
	TEXTURE_STRIPES = 2,
	TEXTURE_WOOD_GRAIN = 3,
	TEXTURE_METAL_BRUSHED = 4,
	TEXTURE_CARBON_FIBER = 5,
	TEXTURE_MARBLE = 6,
	TEXTURE_BRICK = 7,
	TEXTURE_CIRCUIT_BOARD = 8,
	TEXTURE_SCALES = 9,
	TEXTURE_HEXAGON = 10,
	TEXTURE_PLASMA = 11
} t_texture_type;

typedef struct s_texture_system {
	t_texture_type	current_texture;
	bool			active;
	float			time_accumulator;
	float			scale_factor;
	bool			initialized;
	uint32_t		*original_colors;
	int				total_points;
	float			animation_speed;
} t_texture_system;

static t_texture_system g_texture = {
	.current_texture = TEXTURE_NONE,
	.active = false,
	.time_accumulator = 0.0f,
	.scale_factor = 1.0f,
	.initialized = false,
	.original_colors = NULL,
	.total_points = 0,
	.animation_speed = 1.0f
};

// Store original colors for texture blending
static void store_original_texture_colors(t_app *fdf)
{
	if (g_texture.initialized)
		return;
	
	g_texture.total_points = fdf->width * fdf->height;
	
	if (g_texture.original_colors)
		free(g_texture.original_colors);
	
	g_texture.original_colors = malloc(sizeof(uint32_t) * g_texture.total_points);
	if (!g_texture.original_colors)
		return;
	
	// Store original colors
	for (int i = 0; i < g_texture.total_points; i++)
		g_texture.original_colors[i] = fdf->color[i];
	
	g_texture.initialized = true;
	printf("🎨 Texture system initialized with %d colors\n", g_texture.total_points);
}

// Helper function for color blending
static uint32_t blend_colors(uint32_t base_color, uint32_t texture_color, float blend_factor)
{
	uint8_t base_r = (base_color >> 16) & 0xFF;
	uint8_t base_g = (base_color >> 8) & 0xFF;
	uint8_t base_b = base_color & 0xFF;
	
	uint8_t tex_r = (texture_color >> 16) & 0xFF;
	uint8_t tex_g = (texture_color >> 8) & 0xFF;
	uint8_t tex_b = texture_color & 0xFF;
	
	uint8_t final_r = base_r + (uint8_t)((tex_r - base_r) * blend_factor);
	uint8_t final_g = base_g + (uint8_t)((tex_g - base_g) * blend_factor);
	uint8_t final_b = base_b + (uint8_t)((tex_b - base_b) * blend_factor);
	
	return (final_r << 16) | (final_g << 8) | final_b;
}

// Checkerboard texture - classic black and white squares
static void apply_checkerboard_texture(t_app *fdf)
{
	float checker_size = 8.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Create checkerboard pattern
			int checker_x = (int)(x / checker_size);
			int checker_y = (int)(y / checker_size);
			
			bool is_white = ((checker_x + checker_y) % 2) == 0;
			uint32_t texture_color = is_white ? 0xFFFFFF : 0x000000;
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}

// Stripes texture - dynamic color bands
static void apply_stripes_texture(t_app *fdf)
{
	float stripe_width = 6.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Diagonal stripes with animation
			float diagonal_pos = (x + y + g_texture.time_accumulator * 20.0f) / stripe_width;
			int stripe_id = (int)diagonal_pos % 3;
			
			uint32_t texture_color;
			switch (stripe_id)
			{
				case 0: texture_color = 0xFF0000; break; // Red
				case 1: texture_color = 0x00FF00; break; // Green
				case 2: texture_color = 0x0000FF; break; // Blue
				default: texture_color = 0xFFFFFF; break;
			}
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.5f);
		}
	}
}

// Wood grain texture - organic flowing lines
static void apply_wood_grain_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Wood grain pattern with multiple frequencies
			float grain1 = sinf((norm_x * 20.0f + g_texture.time_accumulator * 0.5f) * M_PI);
			float grain2 = sinf((norm_y * 8.0f + norm_x * 2.0f) * M_PI);
			float grain3 = sinf((norm_x * 40.0f + grain1 * 5.0f) * M_PI);
			
			float wood_intensity = (grain1 + grain2 + grain3) / 3.0f;
			wood_intensity = (wood_intensity + 1.0f) / 2.0f; // Normalize to [0,1]
			
			// Wood colors - light to dark brown
			uint32_t light_wood = 0xDEB887; // Burlywood
			uint32_t dark_wood = 0x8B4513;  // Saddle brown
			
			uint32_t texture_color = blend_colors(light_wood, dark_wood, wood_intensity);
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}

// Brushed metal texture - horizontal lines with highlights
static void apply_metal_brushed_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Horizontal brush lines
			float brush_lines = sinf(norm_y * 80.0f * g_texture.scale_factor) * 0.3f;
			
			// Add subtle highlights
			float highlight = sinf((norm_x + g_texture.time_accumulator * 0.8f) * M_PI * 4.0f) * 0.2f;
			
			float metal_intensity = 0.5f + brush_lines + highlight;
			metal_intensity = fmaxf(0.0f, fminf(1.0f, metal_intensity));
			
			// Metal colors - dark to bright silver
			uint32_t dark_metal = 0x404040;
			uint32_t bright_metal = 0xC0C0C0;
			
			uint32_t texture_color = blend_colors(dark_metal, bright_metal, metal_intensity);
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.8f);
		}
	}
}

// Carbon fiber texture - woven pattern
static void apply_carbon_fiber_texture(t_app *fdf)
{
	float weave_size = 4.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Weave pattern calculation
			int weave_x = (int)(x / weave_size) % 4;
			int weave_y = (int)(y / weave_size) % 4;
			
			bool is_fiber_a = ((weave_x + weave_y) % 2) == 0;
			bool is_highlight = (weave_x == 0 || weave_y == 0);
			
			uint32_t texture_color;
			if (is_highlight)
				texture_color = 0x666666; // Light carbon
			else if (is_fiber_a)
				texture_color = 0x1a1a1a; // Dark carbon
			else
				texture_color = 0x000000; // Black
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}

// Marble texture - swirling veins
static void apply_marble_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Marble vein pattern
			float vein1 = sinf((norm_x * 6.0f + norm_y * 4.0f + g_texture.time_accumulator * 0.3f) * M_PI);
			float vein2 = sinf((norm_x * 8.0f - norm_y * 6.0f + g_texture.time_accumulator * 0.2f) * M_PI);
			float vein3 = sinf((norm_x * 12.0f + norm_y * 8.0f) * M_PI);
			
			float marble_intensity = (vein1 + vein2 + vein3) / 3.0f;
			marble_intensity = (marble_intensity + 1.0f) / 2.0f;
			
			// Marble colors - white to gray with dark veins
			uint32_t white_marble = 0xF8F8FF;
			uint32_t gray_marble = 0xC0C0C0;
			uint32_t dark_vein = 0x696969;
			
			uint32_t texture_color;
			if (marble_intensity > 0.8f)
				texture_color = white_marble;
			else if (marble_intensity < 0.2f)
				texture_color = dark_vein;
			else
				texture_color = gray_marble;
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}

// Brick texture - rectangular pattern with mortar
static void apply_brick_texture(t_app *fdf)
{
	float brick_width = 12.0f / g_texture.scale_factor;
	float brick_height = 6.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Brick grid calculation
			int row = (int)(y / brick_height);
			int col = (int)((x + (row % 2) * brick_width / 2) / brick_width);
			
			// Mortar lines
			float local_x = fmodf(x + (row % 2) * brick_width / 2, brick_width);
			float local_y = fmodf(y, brick_height);
			
			bool is_mortar = (local_x < 1.0f || local_x > brick_width - 1.0f || 
							 local_y < 1.0f || local_y > brick_height - 1.0f);
			
			uint32_t texture_color;
			if (is_mortar)
				texture_color = 0xD3D3D3; // Light gray mortar
			else
			{
				// Vary brick colors
				int brick_id = (row * 1000 + col) % 3;
				switch (brick_id)
				{
					case 0: texture_color = 0xB22222; break; // Fire brick
					case 1: texture_color = 0xA0522D; break; // Sienna
					case 2: texture_color = 0x8B4513; break; // Saddle brown
					default: texture_color = 0xB22222; break;
				}
			}
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}

// Circuit board texture - electronic traces
static void apply_circuit_board_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Circuit traces - horizontal and vertical lines
			bool h_trace = (y % 8 == 0 || y % 8 == 1);
			bool v_trace = (x % 12 == 0 || x % 12 == 1);
			bool junction = ((x % 12 < 3) && (y % 8 < 3));
			
			// Add some animated elements
			bool active_trace = ((x + y + (int)(g_texture.time_accumulator * 10.0f)) % 20) < 2;
			
			uint32_t texture_color;
			if (junction)
				texture_color = 0xFFD700; // Gold junction
			else if ((h_trace || v_trace) && active_trace)
				texture_color = 0x00FF00; // Active green trace
			else if (h_trace || v_trace)
				texture_color = 0x00AA00; // Inactive green trace
			else
				texture_color = 0x006600; // Dark green PCB
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}

// Scales texture - fish/dragon scale pattern
static void apply_scales_texture(t_app *fdf)
{
	float scale_size = 8.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Scale pattern with offset rows
			float scale_x = x / scale_size;
			float scale_y = y / scale_size;
			
			// Offset every other row
			if ((int)scale_y % 2 == 1)
				scale_x += 0.5f;
			
			// Distance from scale center
			float local_x = scale_x - floorf(scale_x) - 0.5f;
			float local_y = scale_y - floorf(scale_y) - 0.5f;
			float dist = sqrtf(local_x * local_x + local_y * local_y);
			
			// Scale highlight based on distance and animation
			float highlight = 1.0f - dist * 2.0f;
			highlight = fmaxf(0.0f, highlight);
			
			// Add shimmer effect
			float shimmer = sinf((norm_x * 10.0f + norm_y * 8.0f + g_texture.time_accumulator * 3.0f) * M_PI);
			highlight += shimmer * 0.2f;
			
			// Scale colors
			uint32_t dark_scale = 0x2F4F4F;  // Dark slate gray
			uint32_t bright_scale = 0x87CEEB; // Sky blue
			
			uint32_t texture_color = blend_colors(dark_scale, bright_scale, highlight);
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.7f);
		}
	}
}

// Hexagon texture - honeycomb pattern
static void apply_hexagon_texture(t_app *fdf)
{
	float hex_size = 10.0f / g_texture.scale_factor;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Hexagonal grid calculation (simplified)
			float hex_x = x / hex_size;
			float hex_y = y / hex_size;
			
			// Approximate hexagon pattern
			int grid_x = (int)hex_x;
			int grid_y = (int)hex_y;
			
			// Offset every other row
			if (grid_y % 2 == 1)
				grid_x += 0.5f;
			
			// Distance from hexagon center
			float local_x = hex_x - floorf(hex_x) - 0.5f;
			float local_y = hex_y - floorf(hex_y) - 0.5f;
			float dist = fmaxf(fabsf(local_x), fabsf(local_y) * 0.866f);
			
			bool is_border = dist > 0.4f;
			bool is_center = dist < 0.1f;
			
			uint32_t texture_color;
			if (is_center)
				texture_color = 0xFFD700; // Gold center
			else if (is_border)
				texture_color = 0x000000; // Black border
			else
				texture_color = 0xFFA500; // Orange fill
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.6f);
		}
	}
}

// Plasma texture - animated energy field
static void apply_plasma_texture(t_app *fdf)
{
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Multiple plasma waves
			float plasma1 = sinf((norm_x * 8.0f + g_texture.time_accumulator * 2.0f) * M_PI);
			float plasma2 = sinf((norm_y * 6.0f + g_texture.time_accumulator * 1.5f) * M_PI);
			float plasma3 = sinf(((norm_x + norm_y) * 10.0f + g_texture.time_accumulator * 3.0f) * M_PI);
			float plasma4 = sinf((sqrtf(norm_x * norm_x + norm_y * norm_y) * 12.0f - g_texture.time_accumulator * 4.0f) * M_PI);
			
			float plasma_intensity = (plasma1 + plasma2 + plasma3 + plasma4) / 4.0f;
			plasma_intensity = (plasma_intensity + 1.0f) / 2.0f; // Normalize to [0,1]
			
			// Plasma colors - blue to red spectrum
			uint32_t texture_color;
			if (plasma_intensity < 0.33f)
				texture_color = blend_colors(0x0000FF, 0x00FFFF, plasma_intensity * 3.0f); // Blue to cyan
			else if (plasma_intensity < 0.66f)
				texture_color = blend_colors(0x00FFFF, 0xFFFF00, (plasma_intensity - 0.33f) * 3.0f); // Cyan to yellow
			else
				texture_color = blend_colors(0xFFFF00, 0xFF0000, (plasma_intensity - 0.66f) * 3.0f); // Yellow to red
			
			fdf->color[index] = blend_colors(g_texture.original_colors[index], texture_color, 0.8f);
		}
	}
}

// Main texture system update function
void texture_system_update(t_app *fdf)
{
	if (g_texture.current_texture == TEXTURE_NONE)
		return;
	
	store_original_texture_colors(fdf);
	
	if (!g_texture.original_colors)
		return;
	
	// Update timing
	g_texture.time_accumulator += 0.05f * g_texture.animation_speed;
	
	// Apply current texture
	const char *texture_names[] = {
		"None", "🏁 Checkerboard", "🌈 Stripes", "🌳 Wood Grain", "🔩 Brushed Metal",
		"🏎️ Carbon Fiber", "🏛️ Marble", "🧱 Brick", "💾 Circuit Board",
		"🐉 Scales", "🍯 Hexagon", "⚡ Plasma"
	};
	
	switch (g_texture.current_texture)
	{
		case TEXTURE_NONE:
			break;
		case TEXTURE_CHECKERBOARD:
			apply_checkerboard_texture(fdf);
			break;
		case TEXTURE_STRIPES:
			apply_stripes_texture(fdf);
			break;
		case TEXTURE_WOOD_GRAIN:
			apply_wood_grain_texture(fdf);
			break;
		case TEXTURE_METAL_BRUSHED:
			apply_metal_brushed_texture(fdf);
			break;
		case TEXTURE_CARBON_FIBER:
			apply_carbon_fiber_texture(fdf);
			break;
		case TEXTURE_MARBLE:
			apply_marble_texture(fdf);
			break;
		case TEXTURE_BRICK:
			apply_brick_texture(fdf);
			break;
		case TEXTURE_CIRCUIT_BOARD:
			apply_circuit_board_texture(fdf);
			break;
		case TEXTURE_SCALES:
			apply_scales_texture(fdf);
			break;
		case TEXTURE_HEXAGON:
			apply_hexagon_texture(fdf);
			break;
		case TEXTURE_PLASMA:
			apply_plasma_texture(fdf);
			break;
	}
	
	// Debug output occasionally
	static int debug_counter = 0;
	if (++debug_counter % 300 == 0)
	{
		printf("🎨 Texture: %s (scale: %.1fx, speed: %.1fx)\n", 
			   texture_names[g_texture.current_texture], 
			   g_texture.scale_factor, g_texture.animation_speed);
	}
}

// Toggle texture system (circular buffer)
void texture_system_toggle(void)
{
	// Cycle through texture types
	t_texture_type next_texture = (g_texture.current_texture + 1) % TEXTURE_COUNT;
	
	g_texture.current_texture = next_texture;
	g_texture.time_accumulator = 0.0f;
	
	const char *texture_names[] = {
		"None", "🏁 Checkerboard", "🌈 Stripes", "🌳 Wood Grain", "🔩 Brushed Metal",
		"🏎️ Carbon Fiber", "🏛️ Marble", "🧱 Brick", "💾 Circuit Board",
		"🐉 Scales", "🍯 Hexagon", "⚡ Plasma"
	};
	
	printf("🎨 Texture switched to: %s\n", texture_names[next_texture]);
}

// Check if texture system is active
bool texture_system_is_active(void)
{
	return g_texture.current_texture != TEXTURE_NONE;
}

// Set texture scale
void texture_system_set_scale(float scale)
{
	g_texture.scale_factor = fmaxf(0.1f, fminf(5.0f, scale));
	printf("🎨 Texture scale set to %.1fx\n", g_texture.scale_factor);
}

// Set animation speed
void texture_system_set_speed(float speed)
{
	g_texture.animation_speed = fmaxf(0.0f, fminf(3.0f, speed));
	printf("🎨 Texture animation speed set to %.1fx\n", g_texture.animation_speed);
}

// Cleanup texture system
void texture_system_cleanup(void)
{
	if (g_texture.original_colors)
	{
		free(g_texture.original_colors);
		g_texture.original_colors = NULL;
	}
	
	g_texture.initialized = false;
	g_texture.current_texture = TEXTURE_NONE;
	g_texture.time_accumulator = 0.0f;
	
	printf("🎨 Texture system cleaned up\n");
}
