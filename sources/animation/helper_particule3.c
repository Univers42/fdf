/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_particule3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:04:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:05:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "bench.h"
#include <math.h>

/*
 * Motion integrates wall-clock time (dt in 60ths of a second), so the
 * simulation runs at the same speed at 60 or 700 FPS.
 */
float	ps_delta(void)
{
	static uint64_t	last;
	uint64_t		now;
	float			dt;

	now = bench_now_ns();
	dt = 60.0e-9f * (float)(now - last);
	last = now;
	if (dt < 0.01f || dt > 4.0f)
		dt = 1.0f;
	return (dt);
}

void	ps_transition_step(t_particle_transition *ps)
{
	if (!ps->active)
		return ;
	ps->frame++;
	if (ps->frame >= ps->max_frames)
	{
		ps->active = false;
		ps->frame = 0;
		ps->current_type = ps->target_type;
	}
}

void	ps_update_all(t_particle_transition *ps, float dt)
{
	int	i;

	i = 0;
	while (i < MAX_PARTICLES)
	{
		update_particle(&ps->particles[i], ps->current_type, dt);
		i++;
	}
}

/*
 * Environmental coupling: when the black-hole scene is up, particles
 * feel an inverse-square pull toward the hole and are absorbed once
 * they cross the photon sphere (returns 1).
 */
int	particle_env_forces(t_particle *p, float dt)
{
	t_black_hole	*bh;
	float			d[2];
	float			r2;
	float			g;

	bh = gblackhole();
	if (!gdynbg(NULL)->active || !bh->init
		|| gdynbg(NULL)->current_bg != DYNAMIC_BG_BLACK_HOLE)
		return (0);
	d[0] = gviewport()->w * 0.5f - p->x;
	d[1] = gviewport()->h * 0.5f - p->y;
	r2 = d[0] * d[0] + d[1] * d[1];
	if (r2 < bh->photon_r * bh->photon_r)
		return (1);
	g = 2.2f * bh->photon_r * bh->photon_r / r2;
	if (g > 1.5f)
		g = 1.5f;
	g = g * dt / sqrtf(r2);
	p->vx += d[0] * g;
	p->vy += d[1] * g;
	return (0);
}

void	update_particle(t_particle *p, t_particle_type type, float dt)
{
	int	gone;

	if (!p->active)
		return ;
	p->x += p->vx * dt;
	p->y += p->vy * dt;
	apply_particle_physics(p, type, dt);
	gone = particle_env_forces(p, dt);
	p->lifetime -= dt;
	if (weather_recycle(p, type, gone))
		return ;
	if (gone || p->lifetime <= 0 || p->y < -80.0f
		|| p->y > (float)gviewport()->h + 80.0f
		|| p->x < -80.0f || p->x > (float)gviewport()->w + 80.0f)
		p->active = false;
}
