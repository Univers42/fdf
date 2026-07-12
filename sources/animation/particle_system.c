/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:06:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "bench.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

static void	ps_maybe_spawn_more(t_particle_transition *ps, t_app *fdf,
				float dt)
{
	if (ps->current_type == PARTICLE_NONE)
		return ;
	ps->time_accumulator += dt;
	while (ps->time_accumulator >= 1.0f)
	{
		spawn_particles(ps->current_type, fdf);
		ps->time_accumulator -= 1.0f;
	}
}

void	particles_update(t_app *fdf)
{
	t_particle_transition	*ps;
	float					dt;

	ps = gparticles(NULL);
	if (!ps->active && ps->current_type == PARTICLE_NONE)
		return ;
	dt = ps_delta();
	ps_init_if_needed(ps);
	ps_transition_step(ps);
	ps_update_all(ps, dt);
	ps_maybe_spawn_more(ps, fdf, dt);
	render_particles(fdf);
}

static void	ps_seed_batch(t_particle_transition *ps, t_particle_type type,
		int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		spawn_one_of_type(ps, type, NULL);
		i++;
	}
}

void	transition_start_particles(bool to_particles)
{
	t_particle_transition	*ps;
	t_particle_type			next;

	(void)to_particles;
	ps = gparticles(NULL);
	ps_init_if_needed(ps);
	next = (ps->current_type + 1) % PARTICLE_COUNT;
	ps->active = true;
	ps->frame = 0;
	ps->target_type = next;
	if (next != PARTICLE_NONE)
		ps_seed_batch(ps, next, 400);
}

bool	particles_is_active(void)
{
	t_particle_transition	*ps;

	ps = gparticles(NULL);
	return (ps->active || ps->current_type != PARTICLE_NONE);
}
