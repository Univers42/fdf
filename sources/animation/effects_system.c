#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define EFFECT_TRANSITION_FRAMES 30
#define EFFECT_COUNT 12
#define MAX_RIPPLES 10
#define MAX_LIGHTNING 20

typedef enum e_effect_type {
	EFFECT_NONE = 0,
	EFFECT_SHADOWS = 1,
	EFFECT_RIPPLES = 2,
	EFFECT_LIGHTNING = 3,
	EFFECT_FOG = 4,
	EFFECT_NEON_GLOW = 5,
	EFFECT_WIREFRAME_PULSE = 6,
	EFFECT_COLOR_SHIFT = 7,
	EFFECT_SCREEN_DISTORTION = 8,
	EFFECT_DEPTH_BLUR = 9,
	EFFECT_HOLOGRAM = 10,
	EFFECT_MATRIX_RAIN = 11
} t_effect_type;

typedef struct s_ripple {
	float center_x, center_y;
	float radius;
	float amplitude;
	float frequency;
	bool active;
	int lifetime;
} t_ripple;

typedef struct s_lightning_bolt {
	float start_x, start_y;
	float end_x, end_y;
	float branch_points[6][2]; // Up to 3 branch points
	int branch_count;
	uint32_t color;
	int lifetime;
	bool active;
} t_lightning_bolt;

typedef struct s_effects_system {
	int					frame;
	int					max_frames;
	bool				active;
	t_effect_type		current_effect;
	t_effect_type		target_effect;
	bool				initialized;
	float				time_accumulator;
	
	// Effect-specific data
	t_ripple			ripples[MAX_RIPPLES];
	t_lightning_bolt	lightning[MAX_LIGHTNING];
	float				fog_density;
	float				neon_intensity;
	float				pulse_phase;
	float				color_shift_hue;
	float				distortion_strength;
	uint32_t			*depth_buffer;
	float				hologram_flicker;
	int					matrix_drops[WIN_WIDTH / 20];
} t_effects_system;

static t_effects_system g_effects = {0, EFFECT_TRANSITION_FRAMES, false, EFFECT_NONE, EFFECT_NONE, false, 0.0f, {{0}}, {{0}}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NULL, 0.0f, {0}};

// Utility function to blend colors
static uint32_t blend_colors(uint32_t color1, uint32_t color2, float factor)
{
	int r1 = (color1 >> 16) & 0xFF, g1 = (color1 >> 8) & 0xFF, b1 = color1 & 0xFF;
	int r2 = (color2 >> 16) & 0xFF, g2 = (color2 >> 8) & 0xFF, b2 = color2 & 0xFF;
	
	int r = r1 + (int)((r2 - r1) * factor);
	int g = g1 + (int)((g2 - g1) * factor);
	int b = b1 + (int)((b2 - b1) * factor);
	
	return (r << 16) | (g << 8) | b;
}

// Initialize ripple effect
static void init_ripple(t_ripple *ripple, float x, float y)
{
	ripple->center_x = x;
	ripple->center_y = y;
	ripple->radius = 0.0f;
	ripple->amplitude = 50.0f + (rand() % 100);
	ripple->frequency = 0.1f + (rand() % 20) * 0.01f;
	ripple->active = true;
	ripple->lifetime = 200 + (rand() % 200);
}

// Update ripple effects
static void update_ripples(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	// Spawn new ripples occasionally
	if (rand() % 100 < 5) // 5% chance per frame
	{
		for (int i = 0; i < MAX_RIPPLES; i++)
		{
			if (!g_effects.ripples[i].active)
			{
				init_ripple(&g_effects.ripples[i], 
					rand() % WIN_WIDTH, rand() % WIN_HEIGHT);
				break;
			}
		}
	}
	
	// Update and render active ripples
	for (int i = 0; i < MAX_RIPPLES; i++)
	{
		t_ripple *ripple = &g_effects.ripples[i];
		if (!ripple->active) continue;
		
		ripple->radius += 3.0f;
		ripple->lifetime--;
		
		if (ripple->lifetime <= 0 || ripple->radius > 300.0f)
		{
			ripple->active = false;
			continue;
		}
		
		// Draw ripple circle
		float wave_intensity = ripple->amplitude * expf(-ripple->radius * 0.01f);
		for (int angle = 0; angle < 360; angle += 5)
		{
			float rad = angle * M_PI / 180.0f;
			int x = (int)(ripple->center_x + ripple->radius * cosf(rad));
			int y = (int)(ripple->center_y + ripple->radius * sinf(rad));
			
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			{
				uint32_t wave_color = 0x4080FF + ((int)wave_intensity << 8);
				screen[y * WIN_WIDTH + x] = blend_colors(screen[y * WIN_WIDTH + x], wave_color, 0.6f);
			}
		}
	}
}

// Initialize lightning bolt
static void init_lightning(t_lightning_bolt *bolt)
{
	bolt->start_x = rand() % WIN_WIDTH;
	bolt->start_y = 0;
	
	// Fix the modulo operation with float
	int temp_end_x = (int)bolt->start_x + (rand() % 400 - 200);
	if (temp_end_x < 0) temp_end_x = 0;
	if (temp_end_x >= WIN_WIDTH) temp_end_x = WIN_WIDTH - 1;
	bolt->end_x = (float)temp_end_x;
	
	bolt->end_y = rand() % WIN_HEIGHT;
	
	// Create branch points
	bolt->branch_count = 1 + rand() % 3;
	for (int i = 0; i < bolt->branch_count; i++)
	{
		float t = (i + 1.0f) / (bolt->branch_count + 1.0f);
		bolt->branch_points[i][0] = bolt->start_x + t * (bolt->end_x - bolt->start_x) + (rand() % 100 - 50);
		bolt->branch_points[i][1] = bolt->start_y + t * (bolt->end_y - bolt->start_y);
	}
	
	bolt->color = 0xFFFF00 + (rand() % 0x8080);
	bolt->lifetime = 10 + rand() % 15;
	bolt->active = true;
}

// Update lightning effects
static void update_lightning(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	// Spawn new lightning occasionally
	if (rand() % 200 < 3) // Rare lightning strikes
	{
		for (int i = 0; i < MAX_LIGHTNING; i++)
		{
			if (!g_effects.lightning[i].active)
			{
				init_lightning(&g_effects.lightning[i]);
				break;
			}
		}
	}
	
	// Update and render lightning
	for (int i = 0; i < MAX_LIGHTNING; i++)
	{
		t_lightning_bolt *bolt = &g_effects.lightning[i];
		if (!bolt->active) continue;
		
		bolt->lifetime--;
		if (bolt->lifetime <= 0)
		{
			bolt->active = false;
			continue;
		}
		
		// Draw main bolt
		float intensity = (float)bolt->lifetime / 25.0f;
		uint32_t bolt_color = blend_colors(0x000000, bolt->color, intensity);
		
		// Simple line drawing for lightning
		int dx = abs((int)bolt->end_x - (int)bolt->start_x);
		int dy = abs((int)bolt->end_y - (int)bolt->start_y);
		int x = (int)bolt->start_x, y = (int)bolt->start_y;
		int x_inc = (bolt->start_x < bolt->end_x) ? 1 : -1;
		int y_inc = (bolt->start_y < bolt->end_y) ? 1 : -1;
		int error = dx - dy;
		
		while (1)
		{
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			{
				screen[y * WIN_WIDTH + x] = bolt_color;
				// Add glow effect
				for (int gx = -2; gx <= 2; gx++)
				{
					for (int gy = -2; gy <= 2; gy++)
					{
						int nx = x + gx, ny = y + gy;
						if (nx >= 0 && nx < WIN_WIDTH && ny >= 0 && ny < WIN_HEIGHT)
						{
							float glow_factor = 0.3f / (1.0f + sqrtf(gx*gx + gy*gy));
							screen[ny * WIN_WIDTH + nx] = blend_colors(screen[ny * WIN_WIDTH + nx], bolt_color, glow_factor);
						}
					}
				}
			}
			
			if (x == (int)bolt->end_x && y == (int)bolt->end_y) break;
			
			int e2 = 2 * error;
			if (e2 > -dy) { error -= dy; x += x_inc; }
			if (e2 < dx) { error += dx; y += y_inc; }
		}
	}
}

// Apply fog effect
static void apply_fog_effect(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	g_effects.fog_density = 0.3f + 0.2f * sinf(g_effects.time_accumulator * 0.02f);
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		float fog_factor = g_effects.fog_density * (1.0f - (float)y / WIN_HEIGHT) * 0.5f;
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int pixel = y * WIN_WIDTH + x;
			uint32_t color = screen[pixel];
			
			// Apply fog (blend with gray)
			uint32_t fog_color = 0x808080;
			screen[pixel] = blend_colors(color, fog_color, fog_factor);
		}
	}
}

// Apply neon glow effect
static void apply_neon_glow(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	g_effects.neon_intensity = 0.5f + 0.3f * sinf(g_effects.time_accumulator * 0.1f);
	
	// Create a temporary buffer for glow calculation
	static uint32_t *glow_buffer = NULL;
	if (!glow_buffer)
		glow_buffer = malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(uint32_t));
	
	if (!glow_buffer) return;
	
	// Copy screen to glow buffer
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		glow_buffer[i] = screen[i];
	
	// Apply glow effect
	for (int y = 1; y < WIN_HEIGHT - 1; y++)
	{
		for (int x = 1; x < WIN_WIDTH - 1; x++)
		{
			int pixel = y * WIN_WIDTH + x;
			uint32_t original = glow_buffer[pixel];
			
			// Skip black pixels
			if (original == 0x000000) continue;
			
			// Apply glow to surrounding pixels
			for (int gy = -2; gy <= 2; gy++)
			{
				for (int gx = -2; gx <= 2; gx++)
				{
					int nx = x + gx, ny = y + gy;
					if (nx >= 0 && nx < WIN_WIDTH && ny >= 0 && ny < WIN_HEIGHT)
					{
						int target_pixel = ny * WIN_WIDTH + nx;
						float glow_factor = g_effects.neon_intensity / (1.0f + sqrtf(gx*gx + gy*gy));
						screen[target_pixel] = blend_colors(screen[target_pixel], original, glow_factor * 0.3f);
					}
				}
			}
		}
	}
}

// Apply wireframe pulse effect
static void apply_wireframe_pulse(t_app *fdf)
{
	g_effects.pulse_phase += 0.1f;
	float pulse_intensity = 0.5f + 0.5f * sinf(g_effects.pulse_phase);
	
	// Modify line colors during rendering
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	uint32_t pulse_color = 0xFF0080; // Pink pulse
	
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
	{
		if (screen[i] != 0x000000) // Non-background pixels
		{
			screen[i] = blend_colors(screen[i], pulse_color, pulse_intensity * 0.4f);
		}
	}
}

// Apply color shift effect
static void apply_color_shift(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	g_effects.color_shift_hue += 2.0f;
	if (g_effects.color_shift_hue > 360.0f) g_effects.color_shift_hue -= 360.0f;
	
	float hue_rad = g_effects.color_shift_hue * M_PI / 180.0f;
	float shift_r = 0.5f + 0.5f * sinf(hue_rad);
	float shift_g = 0.5f + 0.5f * sinf(hue_rad + 2.0f * M_PI / 3.0f);
	float shift_b = 0.5f + 0.5f * sinf(hue_rad + 4.0f * M_PI / 3.0f);
	
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
	{
		uint32_t color = screen[i];
		if (color == 0x000000) continue;
		
		int r = (color >> 16) & 0xFF;
		int g = (color >> 8) & 0xFF;
		int b = color & 0xFF;
		
		r = (int)(r * shift_r);
		g = (int)(g * shift_g);
		b = (int)(b * shift_b);
		
		r = (r > 255) ? 255 : r;
		g = (g > 255) ? 255 : g;
		b = (b > 255) ? 255 : b;
		
		screen[i] = (r << 16) | (g << 8) | b;
	}
}

// Apply hologram flicker effect
static void apply_hologram_effect(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	g_effects.hologram_flicker += 0.3f;
	
	// Random flicker lines
	if (rand() % 20 < 3)
	{
		int line_y = rand() % WIN_HEIGHT;
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int pixel = line_y * WIN_WIDTH + x;
			screen[pixel] = blend_colors(screen[pixel], 0x00FFFF, 0.7f);
		}
	}
	
	// Overall transparency flicker
	float flicker = 0.7f + 0.3f * sinf(g_effects.hologram_flicker);
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
	{
		if (screen[i] != 0x000000)
		{
			uint32_t color = screen[i];
			int r = ((color >> 16) & 0xFF) * flicker;
			int g = ((color >> 8) & 0xFF) * flicker;
			int b = (color & 0xFF) * flicker;
			screen[i] = (r << 16) | (g << 8) | b;
		}
	}
}

// Apply matrix rain effect
static void apply_matrix_rain(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	// Initialize drops if needed
	static bool drops_initialized = false;
	if (!drops_initialized)
	{
		for (int i = 0; i < WIN_WIDTH / 20; i++)
		{
			g_effects.matrix_drops[i] = rand() % WIN_HEIGHT;
		}
		drops_initialized = true;
	}
	
	// Update and draw matrix drops
	for (int i = 0; i < WIN_WIDTH / 20; i++)
	{
		int x = i * 20;
		int y = g_effects.matrix_drops[i];
		
		// Draw trail
		for (int trail = 0; trail < 15; trail++)
		{
			int trail_y = y - trail * 2;
			if (trail_y >= 0 && trail_y < WIN_HEIGHT && x < WIN_WIDTH)
			{
				float intensity = 1.0f - (float)trail / 15.0f;
				uint32_t matrix_color = (int)(255 * intensity) << 8; // Green
				int pixel = trail_y * WIN_WIDTH + x;
				screen[pixel] = blend_colors(screen[pixel], matrix_color, intensity * 0.8f);
			}
		}
		
		// Move drop down
		g_effects.matrix_drops[i] += 2;
		if (g_effects.matrix_drops[i] > WIN_HEIGHT + 30)
		{
			g_effects.matrix_drops[i] = -30;
		}
	}
}

// Main effects update function
void effects_update(t_app *fdf)
{
	if (!g_effects.active && g_effects.current_effect == EFFECT_NONE)
		return;
	
	// Initialize if needed
	if (!g_effects.initialized)
	{
		srand((unsigned int)time(NULL) + 54321); // Different seed
		g_effects.initialized = true;
	}
	
	// Handle transitions
	if (g_effects.active)
	{
		g_effects.frame++;
		if (g_effects.frame >= g_effects.max_frames)
		{
			g_effects.active = false;
			g_effects.frame = 0;
			g_effects.current_effect = g_effects.target_effect;
		}
	}
	
	// Update time accumulator
	g_effects.time_accumulator += 1.0f;
	
	// Apply current effect
	const char *effect_names[] = {
		"None", "Shadows", "Ripples", "Lightning", "Fog", "Neon Glow",
		"Wireframe Pulse", "Color Shift", "Screen Distortion", "Depth Blur",
		"Hologram", "Matrix Rain"
	};
	
	switch (g_effects.current_effect)
	{
		case EFFECT_NONE:
			break;
		case EFFECT_SHADOWS:
			update_shadow_effects(fdf);
			break;
		case EFFECT_RIPPLES:
			update_ripples(fdf);
			break;
		case EFFECT_LIGHTNING:
			update_lightning(fdf);
			break;
		case EFFECT_FOG:
			apply_fog_effect(fdf);
			break;
		case EFFECT_NEON_GLOW:
			apply_neon_glow(fdf);
			break;
		case EFFECT_WIREFRAME_PULSE:
			apply_wireframe_pulse(fdf);
			break;
		case EFFECT_COLOR_SHIFT:
			apply_color_shift(fdf);
			break;
		case EFFECT_SCREEN_DISTORTION:
			// TODO: Implement screen distortion
			break;
		case EFFECT_DEPTH_BLUR:
			// TODO: Implement depth blur
			break;
		case EFFECT_HOLOGRAM:
			apply_hologram_effect(fdf);
			break;
		case EFFECT_MATRIX_RAIN:
			apply_matrix_rain(fdf);
			break;
	}
	
	// Debug output occasionally
	static int debug_counter = 0;
	if (++debug_counter % 600 == 0) // Every 10 seconds at 60fps
	{
		printf("Effects: %s active\n", effect_names[g_effects.current_effect]);
	}
}

// Start effect transition (circular buffer)
void transition_start_effects(bool to_effects)
{
	(void)to_effects; // Unused parameter
	
	// Cycle through effect types in circular buffer manner
	t_effect_type next_effect = (g_effects.current_effect + 1) % EFFECT_COUNT;
	
	g_effects.active = true;
	g_effects.frame = 0;
	g_effects.target_effect = next_effect;
	
	const char *effect_names[] = {
		"None", "Shadows", "Ripples", "Lightning", "Fog", "Neon Glow",
		"Wireframe Pulse", "Color Shift", "Screen Distortion", "Depth Blur",
		"Hologram", "Matrix Rain"
	};
	
	printf("Effects system transitioning to: %s\n", effect_names[next_effect]);
}

// Check if effects system is active
bool effects_is_active(void)
{
	return g_effects.active || g_effects.current_effect != EFFECT_NONE;
}

// Cleanup effects system
void effects_cleanup(void)
{
	// Reset all effects data
	for (int i = 0; i < MAX_RIPPLES; i++)
		g_effects.ripples[i].active = false;
	
	for (int i = 0; i < MAX_LIGHTNING; i++)
		g_effects.lightning[i].active = false;
	
	if (g_effects.depth_buffer)
	{
		free(g_effects.depth_buffer);
		g_effects.depth_buffer = NULL;
	}
	
	g_effects.initialized = false;
	g_effects.active = false;
	g_effects.frame = 0;
	g_effects.current_effect = EFFECT_NONE;
	g_effects.target_effect = EFFECT_NONE;
	g_effects.time_accumulator = 0.0f;
	
	printf("Effects system cleaned up\n");
}
