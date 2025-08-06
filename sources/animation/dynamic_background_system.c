#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DYNAMIC_BG_COUNT 12
#define WAVE_FREQUENCY 0.08f

typedef enum e_dynamic_bg_type {
	DYNAMIC_BG_STATIC = 0,
	DYNAMIC_BG_VIBRANT_GRADIENT = 1,
	DYNAMIC_BG_DRAMATIC_CLOUDS = 2,
	DYNAMIC_BG_EPILEPTIC_FLASH = 3,
	DYNAMIC_BG_WATER_RIPPLES = 4,
	DYNAMIC_BG_FIRE_PLASMA = 5,
	DYNAMIC_BG_MATRIX_RAIN = 6,
	DYNAMIC_BG_AURORA_WAVES = 7,
	DYNAMIC_BG_COSMIC_NEBULA = 8,
	DYNAMIC_BG_ELECTRIC_STORM = 9,
	DYNAMIC_BG_LIQUID_METAL = 10,
	DYNAMIC_BG_RAINBOW_VORTEX = 11
} t_dynamic_bg_type;

typedef struct s_dynamic_bg_system {
	t_dynamic_bg_type	current_bg;
	bool				active;
	float				time_accumulator;
	float				intensity;
	bool				initialized;
	uint32_t			*bg_buffer;
	float				animation_speed;
	int					frame_counter;
} t_dynamic_bg_system;

static t_dynamic_bg_system g_dynamic_bg = {
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
static uint32_t lerp_color(uint32_t c1, uint32_t c2, float t)
{
	if (t <= 0.0f) return c1;
	if (t >= 1.0f) return c2;
	
	uint8_t r1 = (c1 >> 16) & 0xFF, g1 = (c1 >> 8) & 0xFF, b1 = c1 & 0xFF;
	uint8_t r2 = (c2 >> 16) & 0xFF, g2 = (c2 >> 8) & 0xFF, b2 = c2 & 0xFF;
	
	uint8_t r = r1 + (uint8_t)((r2 - r1) * t);
	uint8_t g = g1 + (uint8_t)((g2 - g1) * t);
	uint8_t b = b1 + (uint8_t)((b2 - b1) * t);
	
	return (r << 16) | (g << 8) | b;
}

// Apply vibrant gradient background - rainbow waves
static void apply_vibrant_gradient_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			// Normalize coordinates
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Create moving rainbow waves
			float wave1 = sinf((norm_x * 4.0f + time * 2.0f) * M_PI);
			float wave2 = sinf((norm_y * 3.0f + time * 1.5f) * M_PI);
			float wave3 = sinf(((norm_x + norm_y) * 2.0f + time * 3.0f) * M_PI);
			
			// Combine waves for color selection
			float color_factor = (wave1 + wave2 + wave3) / 3.0f;
			color_factor = (color_factor + 1.0f) / 2.0f; // Normalize to [0,1]
			
			// Rainbow spectrum
			uint32_t colors[] = {
				0xFF0000, // Red
				0xFF8000, // Orange
				0xFFFF00, // Yellow
				0x00FF00, // Green
				0x00FFFF, // Cyan
				0x0000FF, // Blue
				0x8000FF, // Purple
				0xFF00FF  // Magenta
			};
			
			int color_idx = (int)(color_factor * 7.0f);
			float local_t = (color_factor * 7.0f) - color_idx;
			
			if (color_idx >= 7) { color_idx = 6; local_t = 1.0f; }
			
			buffer[index] = lerp_color(colors[color_idx], colors[color_idx + 1], local_t);
		}
	}
}

// Apply dramatic clouds background - stormy atmosphere
static void apply_dramatic_clouds_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multi-layer noise for cloud effect
			float cloud1 = sinf((norm_x * 8.0f + time * 0.5f) * M_PI) * 
						  cosf((norm_y * 6.0f + time * 0.3f) * M_PI);
			float cloud2 = sinf((norm_x * 15.0f + time * 0.8f) * M_PI) * 
						  cosf((norm_y * 12.0f + time * 0.6f) * M_PI);
			float cloud3 = sinf(((norm_x + norm_y) * 20.0f + time * 1.2f) * M_PI);
			
			// Combine cloud layers
			float cloud_density = (cloud1 * 0.5f + cloud2 * 0.3f + cloud3 * 0.2f);
			cloud_density = (cloud_density + 1.0f) / 2.0f; // Normalize
			
			// Dark stormy colors
			uint32_t dark_cloud = 0x202030;
			uint32_t light_cloud = 0x808090;
			uint32_t lightning = 0xFFFFBB;
			
			// Add lightning flashes
			float lightning_chance = sinf(time * 15.0f + norm_x * 50.0f);
			if (lightning_chance > 0.98f && cloud_density > 0.7f)
			{
				buffer[index] = lightning;
			}
			else
			{
				buffer[index] = lerp_color(dark_cloud, light_cloud, cloud_density);
			}
		}
	}
}

// Apply epileptic flash background - WARNING: SEIZURE TRIGGER
static void apply_epileptic_flash_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	// Fast flashing colors
	float flash_freq = 20.0f; // Very fast flashing
	float flash_phase = sinf(time * flash_freq);
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multiple flashing patterns
			float pattern1 = sinf((norm_x * 10.0f + time * 25.0f) * M_PI);
			float pattern2 = cosf((norm_y * 8.0f + time * 30.0f) * M_PI);
			float pattern3 = sinf(((norm_x + norm_y) * 15.0f + time * 40.0f) * M_PI);
			
			// Combine patterns
			float flash_intensity = (pattern1 + pattern2 + pattern3 + flash_phase) / 4.0f;
			flash_intensity = (flash_intensity + 1.0f) / 2.0f;
			
			// High contrast flashing colors
			uint32_t colors[] = {0x000000, 0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF};
			int color_idx = (int)(flash_intensity * 7.0f) % 8;
			
			buffer[index] = colors[color_idx];
		}
	}
}

// Apply water ripples background - realistic water simulation
static void apply_water_ripples_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multiple ripple sources
			float ripple1_x = 0.3f + 0.2f * sinf(time * 0.8f);
			float ripple1_y = 0.4f + 0.2f * cosf(time * 0.6f);
			float ripple2_x = 0.7f + 0.15f * sinf(time * 1.2f);
			float ripple2_y = 0.6f + 0.15f * cosf(time * 0.9f);
			float ripple3_x = 0.5f + 0.1f * sinf(time * 1.5f);
			float ripple3_y = 0.3f + 0.1f * cosf(time * 1.1f);
			
			// Calculate distances to ripple sources
			float dist1 = sqrtf((norm_x - ripple1_x) * (norm_x - ripple1_x) + 
							   (norm_y - ripple1_y) * (norm_y - ripple1_y));
			float dist2 = sqrtf((norm_x - ripple2_x) * (norm_x - ripple2_x) + 
							   (norm_y - ripple2_y) * (norm_y - ripple2_y));
			float dist3 = sqrtf((norm_x - ripple3_x) * (norm_x - ripple3_x) + 
							   (norm_y - ripple3_y) * (norm_y - ripple3_y));
			
			// Create ripple waves
			float wave1 = sinf((dist1 * 30.0f - time * 8.0f) * M_PI) * expf(-dist1 * 3.0f);
			float wave2 = sinf((dist2 * 25.0f - time * 6.0f) * M_PI) * expf(-dist2 * 4.0f);
			float wave3 = sinf((dist3 * 35.0f - time * 10.0f) * M_PI) * expf(-dist3 * 5.0f);
			
			// Combine waves
			float water_height = (wave1 + wave2 + wave3) * 0.5f + 0.5f;
			water_height = fmaxf(0.0f, fminf(1.0f, water_height));
			
			// Water colors from deep to shallow
			uint32_t deep_water = 0x001133;
			uint32_t shallow_water = 0x4488BB;
			uint32_t foam = 0xAADDFF;
			
			if (water_height > 0.8f)
				buffer[index] = lerp_color(shallow_water, foam, (water_height - 0.8f) * 5.0f);
			else
				buffer[index] = lerp_color(deep_water, shallow_water, water_height);
		}
	}
}

// Apply fire plasma background - dynamic fire effect
static void apply_fire_plasma_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Fire rises from bottom
			float fire_base = 1.0f - norm_y;
			
			// Turbulent fire pattern
			float turbulence1 = sinf((norm_x * 8.0f + time * 4.0f) * M_PI);
			float turbulence2 = sinf((norm_x * 15.0f + time * 6.0f) * M_PI);
			float turbulence3 = sinf((norm_y * 12.0f + time * 5.0f) * M_PI);
			
			float fire_intensity = fire_base * (0.7f + 0.3f * (turbulence1 + turbulence2 + turbulence3) / 3.0f);
			fire_intensity = fmaxf(0.0f, fminf(1.0f, fire_intensity));
			
			// Fire color gradient
			uint32_t black = 0x000000;
			uint32_t dark_red = 0x330000;
			uint32_t red = 0xFF0000;
			uint32_t orange = 0xFF4400;
			uint32_t yellow = 0xFFFF00;
			uint32_t white = 0xFFFFFF;
			
			if (fire_intensity < 0.2f)
				buffer[index] = lerp_color(black, dark_red, fire_intensity * 5.0f);
			else if (fire_intensity < 0.4f)
				buffer[index] = lerp_color(dark_red, red, (fire_intensity - 0.2f) * 5.0f);
			else if (fire_intensity < 0.6f)
				buffer[index] = lerp_color(red, orange, (fire_intensity - 0.4f) * 5.0f);
			else if (fire_intensity < 0.8f)
				buffer[index] = lerp_color(orange, yellow, (fire_intensity - 0.6f) * 5.0f);
			else
				buffer[index] = lerp_color(yellow, white, (fire_intensity - 0.8f) * 5.0f);
		}
	}
}

// Apply Matrix rain background - digital falling code
static void apply_matrix_rain_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	// Clear to black first
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		buffer[i] = 0x000000;
	
	// Create falling "rain" columns
	int column_width = 20;
	int num_columns = WIN_WIDTH / column_width;
	
	for (int col = 0; col < num_columns; col++)
	{
		// Each column has different timing
		float column_offset = col * 0.7f;
		float fall_speed = 8.0f + (col % 3) * 2.0f;
		
		// Calculate drop position
		float drop_y = fmodf(time * fall_speed + column_offset, WIN_HEIGHT + 200.0f) - 100.0f;
		
		// Draw the falling "code"
		for (int trail = 0; trail < 15; trail++)
		{
			int y = (int)(drop_y - trail * 25);
			if (y >= 0 && y < WIN_HEIGHT)
			{
				for (int dx = 0; dx < column_width - 5; dx++)
				{
					int x = col * column_width + dx + 2;
					if (x >= 0 && x < WIN_WIDTH)
					{
						// Fade trail effect
						float fade = 1.0f - (trail / 15.0f);
						
						// Different shades of green
						if (trail == 0)
							buffer[y * WIN_WIDTH + x] = 0x00FF00; // Bright green head
						else if (trail < 3)
							buffer[y * WIN_WIDTH + x] = 0x00CC00; // Medium green
						else if (trail < 8)
							buffer[y * WIN_WIDTH + x] = (uint32_t)(0x008800 * fade); // Fading green
						else
							buffer[y * WIN_WIDTH + x] = (uint32_t)(0x004400 * fade); // Dark green
					}
				}
			}
		}
	}
}

// Apply aurora waves background - northern lights effect
static void apply_aurora_waves_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Aurora waves flowing horizontally
			float wave1 = sinf((norm_y * 8.0f + norm_x * 2.0f + time * 2.0f) * M_PI);
			float wave2 = sinf((norm_y * 12.0f + norm_x * 1.5f + time * 1.5f) * M_PI);
			float wave3 = sinf((norm_y * 6.0f + norm_x * 3.0f + time * 3.0f) * M_PI);
			
			// Combine waves for aurora intensity
			float aurora_intensity = (wave1 + wave2 + wave3) / 3.0f;
			aurora_intensity = (aurora_intensity + 1.0f) / 2.0f; // Normalize
			
			// Vertical gradient (aurora is stronger at top)
			float height_factor = 1.0f - norm_y;
			aurora_intensity *= height_factor * height_factor;
			
			// Aurora colors
			uint32_t dark_sky = 0x000011;
			uint32_t green_aurora = 0x00FF44;
			uint32_t blue_aurora = 0x0044FF;
			uint32_t purple_aurora = 0x8844FF;
			
			// Color selection based on wave patterns
			if (aurora_intensity > 0.7f)
				buffer[index] = lerp_color(green_aurora, purple_aurora, (aurora_intensity - 0.7f) * 3.33f);
			else if (aurora_intensity > 0.4f)
				buffer[index] = lerp_color(blue_aurora, green_aurora, (aurora_intensity - 0.4f) * 3.33f);
			else if (aurora_intensity > 0.1f)
				buffer[index] = lerp_color(dark_sky, blue_aurora, (aurora_intensity - 0.1f) * 3.33f);
			else
				buffer[index] = dark_sky;
		}
	}
}

// Apply cosmic nebula background - space clouds
static void apply_cosmic_nebula_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Multiple nebula layers with different scales and speeds
			float nebula1 = sinf((norm_x * 4.0f + time * 0.3f) * M_PI) * 
						   cosf((norm_y * 3.0f + time * 0.2f) * M_PI);
			float nebula2 = sinf((norm_x * 8.0f + time * 0.5f) * M_PI) * 
						   cosf((norm_y * 6.0f + time * 0.4f) * M_PI);
			float nebula3 = sinf((norm_x * 12.0f + time * 0.8f) * M_PI) * 
						   cosf((norm_y * 10.0f + time * 0.6f) * M_PI);
			
			// Combine nebula layers
			float nebula_density = (nebula1 * 0.5f + nebula2 * 0.3f + nebula3 * 0.2f);
			nebula_density = (nebula_density + 1.0f) / 2.0f; // Normalize
			
			// Add distance effect (center is brighter)
			float center_dist = sqrtf((norm_x - 0.5f) * (norm_x - 0.5f) + (norm_y - 0.5f) * (norm_y - 0.5f));
			float center_glow = 1.0f - center_dist;
			nebula_density *= center_glow;
			
			// Cosmic colors
			uint32_t space_black = 0x000000;
			uint32_t dark_purple = 0x200040;
			uint32_t bright_purple = 0x8000FF;
			uint32_t pink = 0xFF0080;
			uint32_t white_core = 0xFFFFFF;
			
			if (nebula_density > 0.8f)
				buffer[index] = lerp_color(bright_purple, white_core, (nebula_density - 0.8f) * 5.0f);
			else if (nebula_density > 0.6f)
				buffer[index] = lerp_color(pink, bright_purple, (nebula_density - 0.6f) * 5.0f);
			else if (nebula_density > 0.3f)
				buffer[index] = lerp_color(dark_purple, pink, (nebula_density - 0.3f) * 3.33f);
			else if (nebula_density > 0.1f)
				buffer[index] = lerp_color(space_black, dark_purple, (nebula_density - 0.1f) * 5.0f);
			else
				buffer[index] = space_black;
		}
	}
}

// Apply electric storm background - lightning and energy
static void apply_electric_storm_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	// Dark stormy base
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		buffer[i] = 0x111122;
	
	// Add lightning bolts
	for (int bolt = 0; bolt < 5; bolt++)
	{
		// Each bolt has different timing and position
		float bolt_time = fmodf(time * 3.0f + bolt * 1.7f, 4.0f);
		
		if (bolt_time < 0.1f) // Lightning flash duration
		{
			float flash_intensity = 1.0f - (bolt_time / 0.1f);
			
			// Lightning path
			int start_x = (bolt * 200 + 100) % WIN_WIDTH;
			int start_y = 0;
			int end_x = start_x + (int)(sinf(bolt * 1.3f) * 200.0f);
			int end_y = WIN_HEIGHT;
			
			// Draw jagged lightning bolt
			for (int segment = 0; segment < 20; segment++)
			{
				float t = segment / 20.0f;
				int x = start_x + (int)((end_x - start_x) * t + sinf(t * 10.0f + bolt) * 50.0f);
				int y = start_y + (int)((end_y - start_y) * t);
				
				// Draw lightning with glow
				for (int glow = -5; glow <= 5; glow++)
				{
					for (int gy = -3; gy <= 3; gy++)
					{
						int lx = x + glow;
						int ly = y + gy;
						
						if (lx >= 0 && lx < WIN_WIDTH && ly >= 0 && ly < WIN_HEIGHT)
						{
							float glow_dist = sqrtf(glow * glow + gy * gy);
							float glow_intensity = (1.0f - glow_dist / 6.0f) * flash_intensity;
							
							if (glow_intensity > 0.0f)
							{
								uint32_t lightning_color = 0xCCCCFF; // Electric blue-white
								if (glow_dist < 1.0f)
									lightning_color = 0xFFFFFF; // Pure white core
								
								buffer[ly * WIN_WIDTH + lx] = lightning_color;
							}
						}
					}
				}
			}
		}
	}
}

// Apply liquid metal background - chrome-like flowing effect
static void apply_liquid_metal_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH;
			float norm_y = (float)y / WIN_HEIGHT;
			
			// Flowing metal waves
			float flow1 = sinf((norm_x * 6.0f + norm_y * 2.0f + time * 2.0f) * M_PI);
			float flow2 = sinf((norm_x * 8.0f - norm_y * 3.0f + time * 1.5f) * M_PI);
			float flow3 = sinf((norm_x * 4.0f + norm_y * 4.0f + time * 3.0f) * M_PI);
			
			// Combine flows for metallic reflection
			float metal_reflection = (flow1 + flow2 + flow3) / 3.0f;
			metal_reflection = (metal_reflection + 1.0f) / 2.0f; // Normalize
			
			// Metallic colors - silver, chrome, steel
			uint32_t dark_metal = 0x333333;
			uint32_t medium_metal = 0x888888;
			uint32_t bright_metal = 0xCCCCCC;
			uint32_t chrome_highlight = 0xFFFFFF;
			
			if (metal_reflection > 0.85f)
				buffer[index] = chrome_highlight;
			else if (metal_reflection > 0.6f)
				buffer[index] = lerp_color(bright_metal, chrome_highlight, (metal_reflection - 0.6f) * 4.0f);
			else if (metal_reflection > 0.3f)
				buffer[index] = lerp_color(medium_metal, bright_metal, (metal_reflection - 0.3f) * 3.33f);
			else
				buffer[index] = lerp_color(dark_metal, medium_metal, metal_reflection * 3.33f);
		}
	}
}

// Apply rainbow vortex background - spiraling colors
static void apply_rainbow_vortex_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int index = y * WIN_WIDTH + x;
			
			float norm_x = (float)x / WIN_WIDTH - 0.5f;
			float norm_y = (float)y / WIN_HEIGHT - 0.5f;
			
			// Convert to polar coordinates
			float radius = sqrtf(norm_x * norm_x + norm_y * norm_y);
			float angle = atan2f(norm_y, norm_x);
			
			// Create vortex spiral
			float spiral_angle = angle + radius * 8.0f - time * 4.0f;
			
			// Color based on spiral position
			float color_position = fmodf(spiral_angle / (2.0f * M_PI) + 1.0f, 1.0f);
			
			// Rainbow colors
			uint32_t colors[] = {
				0xFF0000, // Red
				0xFF8000, // Orange
				0xFFFF00, // Yellow
				0x00FF00, // Green
				0x00FFFF, // Cyan
				0x0000FF, // Blue
				0x8000FF, // Purple
				0xFF0000  // Back to red
			};
			
			int color_idx = (int)(color_position * 7.0f);
			float local_t = (color_position * 7.0f) - color_idx;
			
			uint32_t base_color = lerp_color(colors[color_idx], colors[color_idx + 1], local_t);
			
			// Add radial fade
			float fade = 1.0f - radius;
			if (fade < 0.0f) fade = 0.0f;
			
			uint8_t r = ((base_color >> 16) & 0xFF) * fade;
			uint8_t g = ((base_color >> 8) & 0xFF) * fade;
			uint8_t b = (base_color & 0xFF) * fade;
			
			buffer[index] = (r << 16) | (g << 8) | b;
		}
	}
}

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

// Cleanup dynamic background system
void dynamic_background_cleanup(void)
{
	if (g_dynamic_bg.bg_buffer)
	{
		free(g_dynamic_bg.bg_buffer);
		g_dynamic_bg.bg_buffer = NULL;
	}
	
	g_dynamic_bg.initialized = false;
	g_dynamic_bg.current_bg = DYNAMIC_BG_STATIC;
	g_dynamic_bg.time_accumulator = 0.0f;
	g_dynamic_bg.frame_counter = 0;
	
	printf("🎨 Dynamic background system cleaned up\n");
}
