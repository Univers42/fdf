#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



t_dynamic_bg_system g_dynamic_bg = {
	.current_bg = DYNAMIC_BG_STATIC,
	.active = false,
	.time_accumulator = 0.0f,
	.intensity = 1.0f,
	.initialized = false,
	.bg_buffer = NULL,
	.animation_speed = 1.0f,
	.frame_counter = 0
};

// Initialize dynamic background system
static void init_dynamic_background_system(void)
{
	if (g_dynamic_bg.initialized)
		return;
	
	// Allocate background buffer
	g_dynamic_bg.bg_buffer = malloc(sizeof(uint32_t) * WIN_WIDTH * WIN_HEIGHT);
	if (!g_dynamic_bg.bg_buffer)
		return;
	
	g_dynamic_bg.initialized = true;
	printf("🎨 Dynamic Background System initialized with %d effects\n", DYNAMIC_BG_COUNT);
}

// Helper function for smooth color interpolation




// Main dynamic background update function
void dynamic_background_update(t_app *fdf)
{
	if (g_dynamic_bg.current_bg == DYNAMIC_BG_STATIC)
		return;
	
	init_dynamic_background_system();
	
	if (!g_dynamic_bg.bg_buffer)
		return;
	
	// Update timing
	g_dynamic_bg.time_accumulator += WAVE_FREQUENCY * g_dynamic_bg.animation_speed;
	g_dynamic_bg.frame_counter++;
	
	// Apply current background effect
	const char *bg_names[] = {
		"Static", "🌈 Vibrant Gradient", "⛈️ Dramatic Clouds", "⚡ Epileptic Flash", 
		"🌊 Water Ripples", "🔥 Fire Plasma", "💚 Matrix Rain", "🌌 Aurora Waves",
		"🌟 Cosmic Nebula", "⚡ Electric Storm", "🔘 Liquid Metal", "🌪️ Rainbow Vortex"
	};
	
	switch (g_dynamic_bg.current_bg)
	{
		case DYNAMIC_BG_STATIC:
			break;
		case DYNAMIC_BG_VIBRANT_GRADIENT:
			apply_vibrant_gradient_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_DRAMATIC_CLOUDS:
			apply_dramatic_clouds_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_EPILEPTIC_FLASH:
			apply_epileptic_flash_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_WATER_RIPPLES:
			apply_water_ripples_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_FIRE_PLASMA:
			apply_fire_plasma_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_MATRIX_RAIN:
			apply_matrix_rain_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_AURORA_WAVES:
			apply_aurora_waves_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_COSMIC_NEBULA:
			apply_cosmic_nebula_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_ELECTRIC_STORM:
			apply_electric_storm_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_LIQUID_METAL:
			apply_liquid_metal_bg(g_dynamic_bg.bg_buffer);
			break;
		case DYNAMIC_BG_RAINBOW_VORTEX:
			apply_rainbow_vortex_bg(g_dynamic_bg.bg_buffer);
			break;
	}
	
	// Copy dynamic background to main renderer buffer
	uint32_t *main_buffer = (uint32_t *)fdf->renderer.data;
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		main_buffer[i] = g_dynamic_bg.bg_buffer[i];
	
	// Debug output occasionally
	static int debug_counter = 0;
	if (++debug_counter % 300 == 0) // Every 5 seconds
	{
		printf("🎨 Dynamic Background: %s (speed: %.1fx)\n", 
			   bg_names[g_dynamic_bg.current_bg], g_dynamic_bg.animation_speed);
	}
}

// Start dynamic background transition (circular buffer)
void dynamic_background_toggle(void)
{
	// Cycle through background types
	t_dynamic_bg_type next_bg = (g_dynamic_bg.current_bg + 1) % DYNAMIC_BG_COUNT;
	
	g_dynamic_bg.current_bg = next_bg;
	g_dynamic_bg.time_accumulator = 0.0f;
	g_dynamic_bg.frame_counter = 0;
	
	const char *bg_names[] = {
		"Static", "🌈 Vibrant Gradient", "⛈️ Dramatic Clouds", "⚡ Epileptic Flash", 
		"🌊 Water Ripples", "🔥 Fire Plasma", "💚 Matrix Rain", "🌌 Aurora Waves",
		"🌟 Cosmic Nebula", "⚡ Electric Storm", "🔘 Liquid Metal", "🌪️ Rainbow Vortex"
	};
	
	printf("🎨 Dynamic Background switched to: %s\n", bg_names[next_bg]);
	
	// Special warning for epileptic flash
	if (next_bg == DYNAMIC_BG_EPILEPTIC_FLASH)
	{
		printf("⚠️  WARNING: EPILEPTIC FLASH MODE - SEIZURE TRIGGER! ⚠️\n");
	}
}

// Check if dynamic background is active
bool dynamic_background_is_active(void)
{
	return g_dynamic_bg.current_bg != DYNAMIC_BG_STATIC;
}

// Set animation speed
void dynamic_background_set_speed(float speed)
{
	g_dynamic_bg.animation_speed = fmaxf(0.1f, fminf(5.0f, speed));
	printf("🎨 Dynamic background speed set to %.1fx\n", g_dynamic_bg.animation_speed);
}

