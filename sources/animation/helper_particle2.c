/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_particle2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:59:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:05:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
 * Per-particle style: lifetime fade (in fast, out slow), depth-layer
 * dimming, per-type color effects (fire cools, stars twinkle) and
 * additive blending for the light emitters.
 */
static void	part_style(t_particle *p, t_particle_type t, struct s_pdraw *d)
{
	float	age;
	float	a;

	age = (float)(p->life0 - p->lifetime);
	a = age / 12.0f;
	if ((float)p->lifetime / 60.0f < a)
		a = (float)p->lifetime / 60.0f;
	if (a > 1.0f)
		a = 1.0f;
	d->alpha = a * (0.55f + 0.45f * p->z);
	d->size = (int)(p->size * (0.55f + 0.45f * p->z) * 2.2f);
	d->px = (int)p->x;
	d->py = (int)p->y;
	d->color = p->color;
	d->add = (t == PARTICLE_FIRE || t == PARTICLE_SPARKS
			|| t == PARTICLE_STARS);
	if (t == PARTICLE_FIRE)
		d->color = fire_ramp(age / (float)(p->life0 + 1));
	else if (t == PARTICLE_STARS)
		d->alpha *= 0.55f + 0.45f * sinf(age * 0.11f + p->phase);
	else if (t == PARTICLE_SMOKE || t == PARTICLE_DUST)
		d->alpha *= 0.45f;
	else if (t == PARTICLE_BUBBLES)
		d->alpha *= 0.55f;
}

void	render_particles(t_app *fdf)
{
	t_particle_transition	*ps;
	uint32_t				*screen;
	int						i;
	struct s_pdraw			d;

	ps = gparticles(NULL);
	screen = (uint32_t *)fdf->renderer.data;
	i = -1;
	while (++i < MAX_PARTICLES)
	{
		if (!ps->particles[i].active)
			continue ;
		part_style(&ps->particles[i], ps->current_type, &d);
		if (d.alpha <= 0.003f || d.size < 1)
			continue ;
		if (ps->current_type == PARTICLE_RAIN)
			draw_particle_streak(screen, &d, ps->particles[i].vx,
				ps->particles[i].vy);
		else
			draw_particle_soft(screen, &d);
	}
}

void	spawn_one_of_type(t_particle_transition *ps,
		t_particle_type type, t_app *fdf)
{
	int	j;

	j = 0;
	while (j < MAX_PARTICLES)
	{
		if (!ps->particles[j].active)
		{
			init_particle(&ps->particles[j], type, fdf);
			break ;
		}
		j++;
	}
}

void	spawn_particles(t_particle_type type, t_app *fdf)
{
	const int				*rate;
	t_particle_transition	*ps;
	int						want;
	int						i;

	ps = gparticles(NULL);
	rate = ps_rate_tbl();
	if (type > PARTICLE_NONE && type < PARTICLE_COUNT)
		want = rate[type];
	else
		want = 3;
	i = 0;
	while (i < want)
	{
		spawn_one_of_type(ps, type, fdf);
		i++;
	}
}

void	ps_init_if_needed(t_particle_transition *ps)
{
	int	i;

	if (ps->initialized)
		return ;
	i = 0;
	while (i < MAX_PARTICLES)
	{
		ps->particles[i].active = false;
		i++;
	}
	ps->initialized = true;
}
