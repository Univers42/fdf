/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:12:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:19:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

#include <stdlib.h>
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

// Cleanup particle system
void particles_cleanup(void)
{
	for (int i = 0; i < MAX_PARTICLES; i++)
		g_particle_system.particles[i].active = false;
		
	g_particle_system.initialized = false;
	g_particle_system.active = false;
	g_particle_system.frame = 0;
	g_particle_system.current_type = PARTICLE_NONE;
	g_particle_system.target_type = PARTICLE_NONE;
	g_particle_system.time_accumulator = 0.0f;
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
