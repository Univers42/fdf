#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

t_texture_system g_texture = {
	.current_texture =	TEXTURE_NONE,
	.active =			false,
	.time_accumulator =	0.0f,
	.scale_factor =		1.0f,
	.initialized =		false,
	.original_colors =	NULL,
	.total_points =		0,
	.animation_speed =	1.0f
};



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
		ft_printf("🎨 Texture: %s (scale: %.1fx, speed: %.1fx)\n", 
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
	
	ft_printf("🎨 Texture switched to: %s\n", texture_names[next_texture]);
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
	ft_printf("🎨 Texture scale set to %.1fx\n", g_texture.scale_factor);
}

// Set animation speed
void texture_system_set_speed(float speed)
{
	g_texture.animation_speed = fmaxf(0.0f, fminf(3.0f, speed));
	ft_printf("🎨 Texture animation speed set to %.1fx\n", g_texture.animation_speed);
}

