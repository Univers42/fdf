#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DANCE_MOVE_COUNT 8
#define DANCE_TRANSITION_FRAMES 120
#define DANCE_HOLD_FRAMES 180

typedef enum e_dance_move {
	DANCE_NONE = 0,
	DANCE_SPIN = 1,
	DANCE_BOUNCE = 2,
	DANCE_WAVE_MOTION = 3,
	DANCE_TWIST = 4,
	DANCE_EXPAND_CONTRACT = 5,
	DANCE_FIGURE_EIGHT = 6,
	DANCE_WOBBLE = 7
} t_dance_move;

typedef struct s_dance_system {
	bool				active;
	t_dance_move		current_move;
	t_dance_move		next_move;
	float				time_accumulator;
	float				move_intensity;
	int					move_frame;
	int					hold_frame;
	bool				transitioning;
	bool				auto_sequence;
	float				*original_points;
	bool				initialized;
	int					total_points;
	float				rhythm_multiplier;
} t_dance_system;

static t_dance_system g_dance = {
	.active = false,
	.current_move = DANCE_NONE,
	.next_move = DANCE_SPIN,
	.time_accumulator = 0.0f,
	.move_intensity = 1.0f,
	.move_frame = 0,
	.hold_frame = 0,
	.transitioning = false,
	.auto_sequence = true,
	.original_points = NULL,
	.initialized = false,
	.total_points = 0,
	.rhythm_multiplier = 1.0f
};

// Store original geometry for dance moves
static void store_original_dance_points(t_app *fdf)
{
	if (g_dance.initialized)
		return;
	
	g_dance.total_points = fdf->width * fdf->height;
	
	if (g_dance.original_points)
		free(g_dance.original_points);
	
	g_dance.original_points = malloc(sizeof(float) * g_dance.total_points);
	if (!g_dance.original_points)
		return;
	
	// Store original Z values
	for (int i = 0; i < g_dance.total_points; i++)
		g_dance.original_points[i] = fdf->points[i];
	
	g_dance.initialized = true;
	printf("🕺 Dance system initialized with %d points - GET READY TO PARTY! 🕺\n", g_dance.total_points);
}

// Apply CRAZY spin dance move - object spins while doing geometric transformations
static void apply_dance_spin(t_app *fdf)
{
	float spin_speed = 0.15f * g_dance.rhythm_multiplier; // Much faster!
	
	// MULTIPLE axis rotations for crazy spinning
	transformation_stack_rotate_y(&fdf->transformation_stack, spin_speed);
	transformation_stack_rotate_x(&fdf->transformation_stack, spin_speed * 0.7f);
	transformation_stack_rotate_z(&fdf->transformation_stack, spin_speed * 0.3f);
	
	// Add WILD geometric deformation while spinning
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create SPINNING wave effect
			float spiral_angle = sqrtf(norm_x * norm_x + norm_y * norm_y) * 8.0f + g_dance.time_accumulator * 5.0f;
			float spiral_effect = sinf(spiral_angle) * 30.0f * g_dance.move_intensity;
			
			fdf->points[index] = g_dance.original_points[index] + spiral_effect;
		}
	}
}

// Apply INSANE bounce dance move - object bounces with extreme deformation
static void apply_dance_bounce(t_app *fdf)
{
	float bounce_freq = 8.0f * g_dance.rhythm_multiplier; // Super fast bouncing!
	float bounce_height = 50.0f * g_dance.move_intensity;
	
	// Vertical bouncing motion with EXTREME amplitude
	float bounce_y = sinf(g_dance.time_accumulator * bounce_freq) * bounce_height;
	
	// CRAZY squash and stretch effect
	float squash_factor = 1.0f + (sinf(g_dance.time_accumulator * bounce_freq * 2.0f) * 0.8f);
	
	// Apply bounce translation
	transformation_stack_translate(&fdf->transformation_stack, 0, bounce_y * 0.2f, 0);
	
	// Apply EXTREME squash/stretch to geometry
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float original_z = g_dance.original_points[index];
			
			// Distance from center affects squash intensity
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			float dist_from_center = sqrtf((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));
			float max_dist = sqrtf(center_x * center_x + center_y * center_y);
			float dist_factor = 1.0f - (dist_from_center / max_dist);
			
			// Extreme squash effect with distance falloff
			float final_squash = squash_factor * (1.0f + dist_factor * 2.0f);
			fdf->points[index] = original_z * final_squash;
		}
	}
}

// Apply WILD wave motion dance - creates massive traveling waves
static void apply_dance_wave_motion(t_app *fdf)
{
	float wave_amplitude = 40.0f * g_dance.move_intensity;
	float wave_freq = 3.0f * g_dance.rhythm_multiplier;
	
	// Figure-8 movement pattern with HUGE amplitude
	float move_x = sinf(g_dance.time_accumulator * wave_freq) * 25.0f;
	float move_z = sinf(g_dance.time_accumulator * wave_freq * 2.0f) * 15.0f;
	
	transformation_stack_translate(&fdf->transformation_stack, move_x * 0.1f, 0, move_z * 0.1f);
	
	// MASSIVE wave deformation through the geometry
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Multiple HUGE traveling waves
			float wave_offset = (norm_x + norm_y) * M_PI * 4.0f;
			float wave1 = sinf(g_dance.time_accumulator * wave_freq * 4.0f + wave_offset) * wave_amplitude;
			
			// Add interference patterns
			float wave2 = sinf(g_dance.time_accumulator * wave_freq * 2.5f + norm_x * M_PI * 6.0f) * wave_amplitude * 0.7f;
			float wave3 = cosf(g_dance.time_accumulator * wave_freq * 3.2f + norm_y * M_PI * 5.0f) * wave_amplitude * 0.5f;
			
			fdf->points[index] = g_dance.original_points[index] + wave1 + wave2 + wave3;
		}
	}
}

// Apply EXTREME twist dance move - object performs corkscrew motion
static void apply_dance_twist(t_app *fdf)
{
	float twist_speed = 0.2f * g_dance.rhythm_multiplier; // Much faster!
	float twist_amplitude = 60.0f * g_dance.move_intensity;
	
	// INSANE corkscrew rotation on all axes
	transformation_stack_rotate_y(&fdf->transformation_stack, twist_speed);
	transformation_stack_rotate_x(&fdf->transformation_stack, twist_speed * 0.8f);
	transformation_stack_rotate_z(&fdf->transformation_stack, twist_speed * 0.6f);
	
	// EXTREME spiral deformation
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			
			float dx = x - center_x;
			float dy = y - center_y;
			float distance = sqrtf(dx * dx + dy * dy);
			
			// CRAZY spiral twist based on distance and time
			float twist_factor = distance * 0.2f + g_dance.time_accumulator * twist_speed * 20.0f;
			float twist_effect = sinf(twist_factor) * twist_amplitude;
			
			// Add secondary twist for more chaos
			float secondary_twist = cosf(twist_factor * 1.7f + g_dance.time_accumulator * 3.0f) * twist_amplitude * 0.6f;
			
			fdf->points[index] = g_dance.original_points[index] + twist_effect + secondary_twist;
		}
	}
}

// Apply CRAZY expand/contract dance move - object breathes WILDLY
static void apply_dance_expand_contract(t_app *fdf)
{
	float pulse_freq = 6.0f * g_dance.rhythm_multiplier; // Much faster breathing!
	float scale_amplitude = 0.8f; // HUGE breathing effect
	float scale_factor = 1.0f + sinf(g_dance.time_accumulator * pulse_freq) * scale_amplitude * g_dance.move_intensity;
	
	// EXTREME scaling with pulsation
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float original_z = g_dance.original_points[index];
			
			// Distance-based scaling for more dramatic effect
			float center_x = fdf->width / 2.0f;
			float center_y = fdf->height / 2.0f;
			float dx = (x - center_x) / center_x;
			float dy = (y - center_y) / center_y;
			float dist_factor = sqrtf(dx * dx + dy * dy);
			
			// Different scaling based on distance
			float local_scale = scale_factor * (1.0f + dist_factor * 0.5f);
			
			fdf->points[index] = original_z * local_scale;
		}
	}
	
	// Add rotation during breathing for extra effect
	float breath_rotation = sinf(g_dance.time_accumulator * pulse_freq) * 0.05f;
	transformation_stack_rotate_y(&fdf->transformation_stack, breath_rotation);
	transformation_stack_rotate_x(&fdf->transformation_stack, breath_rotation * 0.7f);
}

// Apply INSANE figure-eight dance move - complex orbital motion
static void apply_dance_figure_eight(t_app *fdf)
{
	float orbit_freq = 2.5f * g_dance.rhythm_multiplier;
	float orbit_size = 40.0f * g_dance.move_intensity;
	
	// MASSIVE figure-8 orbital motion
	float t = g_dance.time_accumulator * orbit_freq;
	float move_x = sinf(t) * orbit_size;
	float move_y = sinf(t * 2.0f) * orbit_size * 0.8f;
	float move_z = cosf(t * 1.3f) * orbit_size * 0.6f;
	
	transformation_stack_translate(&fdf->transformation_stack, 
		move_x * 0.05f, move_y * 0.05f, move_z * 0.05f);
	
	// CRAZY synchronized rotation on all axes
	transformation_stack_rotate_x(&fdf->transformation_stack, sinf(t * 2.2f) * 0.08f);
	transformation_stack_rotate_y(&fdf->transformation_stack, cosf(t * 1.8f) * 0.1f);
	transformation_stack_rotate_z(&fdf->transformation_stack, sinf(t * 3.1f) * 0.06f);
	
	// Add geometric distortion following the orbital pattern
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create orbital wave effect
			float orbital_wave = sinf(t + norm_x * M_PI * 2.0f) * cosf(t * 1.5f + norm_y * M_PI * 3.0f);
			float distortion = orbital_wave * 25.0f * g_dance.move_intensity;
			
			fdf->points[index] = g_dance.original_points[index] + distortion;
		}
	}
}

// Apply CHAOTIC wobble dance move - complete madness!
static void apply_dance_wobble(t_app *fdf)
{
	float wobble_freq = 8.0f * g_dance.rhythm_multiplier; // SUPER fast!
	float wobble_intensity = g_dance.move_intensity;
	
	// INSANE multi-frequency wobbling on ALL axes
	float wobble_x = (sinf(g_dance.time_accumulator * wobble_freq) + 
					 sinf(g_dance.time_accumulator * wobble_freq * 2.7f) * 0.7f +
					 sinf(g_dance.time_accumulator * wobble_freq * 4.3f) * 0.4f) * 0.05f;
	float wobble_y = (cosf(g_dance.time_accumulator * wobble_freq * 1.9f) + 
					 sinf(g_dance.time_accumulator * wobble_freq * 3.1f) * 0.6f +
					 cosf(g_dance.time_accumulator * wobble_freq * 5.7f) * 0.3f) * 0.04f;
	float wobble_z = (sinf(g_dance.time_accumulator * wobble_freq * 1.4f) + 
					 cosf(g_dance.time_accumulator * wobble_freq * 3.8f) * 0.8f +
					 sinf(g_dance.time_accumulator * wobble_freq * 6.2f) * 0.2f) * 0.03f;
	
	transformation_stack_rotate_x(&fdf->transformation_stack, wobble_x * wobble_intensity);
	transformation_stack_rotate_y(&fdf->transformation_stack, wobble_y * wobble_intensity);
	transformation_stack_rotate_z(&fdf->transformation_stack, wobble_z * wobble_intensity);
	
	// EXTREME geometric wobble - total chaos!
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Multiple CHAOTIC wobble frequencies
			float wobble1 = sinf((norm_x + g_dance.time_accumulator * wobble_freq * 1.2f) * M_PI * 6.0f);
			float wobble2 = cosf((norm_y + g_dance.time_accumulator * wobble_freq * 1.8f) * M_PI * 4.0f);
			float wobble3 = sinf(((norm_x + norm_y) + g_dance.time_accumulator * wobble_freq * 2.3f) * M_PI * 5.0f);
			float wobble4 = cosf((norm_x * norm_y + g_dance.time_accumulator * wobble_freq * 0.7f) * M_PI * 8.0f);
			
			float total_wobble = (wobble1 + wobble2 + wobble3 + wobble4) * 15.0f * wobble_intensity;
			
			fdf->points[index] = g_dance.original_points[index] + total_wobble;
		}
	}
}

// Main dance system update function
void dance_system_update(t_app *fdf)
{
	if (!g_dance.active)
		return;
	
	store_original_dance_points(fdf);
	
	if (!g_dance.original_points)
		return;
	
	// Update dance timing - MUCH faster for more energy!
	g_dance.time_accumulator += 0.15f; // Increased from 0.05f
	g_dance.move_frame++;
	
	// Handle automatic dance sequence
	if (g_dance.auto_sequence && !g_dance.transitioning)
	{
		g_dance.hold_frame++;
		
		// Switch moves more frequently for more excitement!
		if (g_dance.hold_frame >= DANCE_HOLD_FRAMES)
		{
			g_dance.transitioning = true;
			g_dance.hold_frame = 0;
			g_dance.move_frame = 0;
			
			// Select next dance move
			t_dance_move next_move = (g_dance.current_move + 1) % DANCE_MOVE_COUNT;
			if (next_move == DANCE_NONE) next_move = DANCE_SPIN; // Skip NONE
			g_dance.next_move = next_move;
		}
	}
	
	// Handle dance move transitions
	if (g_dance.transitioning)
	{
		float transition_progress = (float)g_dance.move_frame / DANCE_TRANSITION_FRAMES;
		
		if (transition_progress >= 1.0f)
		{
			g_dance.current_move = g_dance.next_move;
			g_dance.transitioning = false;
			g_dance.move_frame = 0;
		}
		else
		{
			// Smooth intensity transition
			g_dance.move_intensity = sinf(transition_progress * M_PI) * 0.5f + 0.5f;
		}
	}
	else
	{
		// MAXIMUM intensity when not transitioning!
		g_dance.move_intensity = 1.5f; // Even more intense!
	}
	
	// Apply current dance move with EXTREME effects
	const char *dance_names[] = {
		"None", "🌪️ SPIN TORNADO", "⚡ MEGA BOUNCE", "🌊 TSUNAMI WAVES", "🌀 TWIST MADNESS", 
		"💨 BREATHING BEAST", "♾️ FIGURE INFINITY", "🎪 CHAOS WOBBLE"
	};
	
	switch (g_dance.current_move)
	{
		case DANCE_NONE:
			break;
		case DANCE_SPIN:
			apply_dance_spin(fdf);
			break;
		case DANCE_BOUNCE:
			apply_dance_bounce(fdf);
			break;
		case DANCE_WAVE_MOTION:
			apply_dance_wave_motion(fdf);
			break;
		case DANCE_TWIST:
			apply_dance_twist(fdf);
			break;
		case DANCE_EXPAND_CONTRACT:
			apply_dance_expand_contract(fdf);
			break;
		case DANCE_FIGURE_EIGHT:
			apply_dance_figure_eight(fdf);
			break;
		case DANCE_WOBBLE:
			apply_dance_wobble(fdf);
			break;
	}
	
	// Debug output occasionally with emojis for excitement!
	static int debug_counter = 0;
	if (++debug_counter % 200 == 0) // More frequent updates
	{
		printf("🕺 DANCING: %s (intensity: %.1f, auto: %s) 🕺\n", 
			   dance_names[g_dance.current_move], 
			   g_dance.move_intensity,
			   g_dance.auto_sequence ? "ON" : "OFF");
	}
}

// Start/stop dancing system
void dance_system_toggle(void)
{
	g_dance.active = !g_dance.active;
	
	if (g_dance.active)
	{
		g_dance.current_move = DANCE_SPIN;
		g_dance.time_accumulator = 0.0f;
		g_dance.move_frame = 0;
		g_dance.hold_frame = 0;
		g_dance.transitioning = false;
		printf("🎉🕺 ULTIMATE DANCE MODE ACTIVATED! GET READY FOR THE SHOW! 🕺🎉\n");
		printf("💃 Your 3D model is about to PARTY HARD! 💃\n");
	}
	else
	{
		printf("🛑 Dance mode deactivated - party's over! 🛑\n");
	}
}

// Check if dancing is active
bool dance_system_is_active(void)
{
	return g_dance.active;
}

// Cleanup dance system
void dance_system_cleanup(void)
{
	if (g_dance.original_points)
	{
		free(g_dance.original_points);
		g_dance.original_points = NULL;
	}
	
	g_dance.initialized = false;
	g_dance.active = false;
	g_dance.current_move = DANCE_NONE;
	g_dance.time_accumulator = 0.0f;
	g_dance.move_frame = 0;
	g_dance.hold_frame = 0;
	g_dance.transitioning = false;
	
	printf("🕺 Dance system cleaned up - time to rest! 🕺\n");
}

// Set dance rhythm speed
void dance_system_set_rhythm(float multiplier)
{
	g_dance.rhythm_multiplier = fmaxf(0.1f, fminf(5.0f, multiplier)); // Allow even faster!
	printf("🎵 Dance rhythm set to %.1fx speed - FEEL THE BEAT! 🎵\n", g_dance.rhythm_multiplier);
}

// Toggle auto-sequence mode
void dance_system_toggle_auto_sequence(void)
{
	g_dance.auto_sequence = !g_dance.auto_sequence;
	printf("🎭 Dance auto-sequence %s 🎭\n", g_dance.auto_sequence ? "enabled" : "disabled");
}
