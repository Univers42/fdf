#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


t_dance_system g_dance = {
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
void store_original_dance_points(t_app *fdf)
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
