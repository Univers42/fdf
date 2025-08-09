/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:12:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:55:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>

// Cleanup dance system
void	dance_system_cleanup(void)
{
	t_dance_system	*d;

	d = gdance(NULL);
	if (d->original_points)
	{
		free(d->original_points);
		d->original_points = NULL;
	}
	d->initialized = false;
	d->active = false;
	d->current_move = DANCE_NONE;
	d->time_accumulator = 0.0f;
	d->move_frame = 0;
	d->hold_frame = 0;
	d->transitioning = false;
	ft_printf("🕺 Dance system cleaned up - time to rest! 🕺\n");
}

// Cleanup object effects system
void	object_effects_cleanup(void)
{
	t_object_effects_system	*oe;

	oe = gobjfx(NULL);
	if (oe->original_points)
	{
		free(oe->original_points);
		oe->original_points = NULL;
	}
	oe->initialized = false;
	oe->current_effect = OBJ_EFFECT_NONE;
	oe->time_accumulator = 0.0f;
	oe->intensity = 1.0f;
	ft_printf("Object effects system cleaned up\n");
}

// Cleanup particle system
void	particles_cleanup(void)
{
	t_particle_transition	*ps;
	int						i;

	ps = gparticles(NULL);
	i = -1;
	while (++i < MAX_PARTICLES)
		ps->particles[i].active = false;
	ps->initialized = false;
	ps->active = false;
	ps->frame = 0;
	ps->current_type = PARTICLE_NONE;
	ps->target_type = PARTICLE_NONE;
	ps->time_accumulator = 0.0f;
}

// Cleanup texture system
void	texture_system_cleanup(void)
{
	t_texture_system	*t;

	t = gtexture(NULL);
	if (t->original_colors)
	{
		free(t->original_colors);
		t->original_colors = NULL;
	}
	t->initialized = false;
	t->current_texture = TEXTURE_NONE;
	t->time_accumulator = 0.0f;
	ft_printf("🎨 Texture system cleaned up\n");
}
