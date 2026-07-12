/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_physics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/* Falling weather: gravity, terminal velocity, sinusoidal snow flutter. */
static void	phys_fall(t_particle *p, t_particle_type type, float dt)
{
	if (type == PARTICLE_SNOW)
	{
		p->vx = 0.35f * p->z + sinf((p->life0 - p->lifetime) * 0.045f
				+ p->phase) * 0.8f * p->z;
		if (p->vy < 2.6f * p->z)
			p->vy += 0.02f * dt;
	}
	else if (type == PARTICLE_RAIN)
	{
		p->vy += 0.55f * dt;
		if (p->vy > 24.0f * p->z)
			p->vy = 24.0f * p->z;
	}
}

/* Buoyant types: fire and smoke rise with turbulence, bubbles wobble. */
static void	phys_rise(t_particle *p, t_particle_type type, float dt)
{
	if (type == PARTICLE_FIRE)
	{
		p->vy -= 0.13f * dt;
		if (p->vy < -6.5f)
			p->vy = -6.5f;
		p->vx += sinf((p->life0 - p->lifetime) * 0.17f + p->phase)
			* 0.09f * dt;
		p->size *= 1.0f - 0.012f * dt;
	}
	else if (type == PARTICLE_SMOKE)
	{
		p->vy -= 0.045f * dt;
		p->vx = sinf((p->life0 - p->lifetime) * 0.05f + p->phase) * 0.9f;
		p->size *= 1.0f + 0.006f * dt;
	}
	else if (type == PARTICLE_BUBBLES)
	{
		p->vy -= 0.035f * dt;
		if (p->vy < -4.0f)
			p->vy = -4.0f;
		p->vx = sinf((p->life0 - p->lifetime) * 0.09f + p->phase) * 1.1f;
	}
}

/* Sparks are ballistic and bounce off the ground; dust drifts. */
static void	phys_misc(t_particle *p, t_particle_type type, float dt)
{
	if (type == PARTICLE_SPARKS)
	{
		p->vy += 0.32f * dt;
		p->vx *= 1.0f - 0.012f * dt;
		if (p->y > gviewport()->h - 2.0f && p->vy > 0.0f)
		{
			p->y = (float)gviewport()->h - 2.0f;
			p->vy *= -0.45f;
			p->vx *= 0.7f;
			if (p->vy > -1.0f && p->lifetime > 20.0f)
				p->lifetime = 20.0f;
		}
	}
	else if (type == PARTICLE_DUST)
	{
		p->vx += 0.0012f * dt * (float)(ft_rand() % 100 - 50);
		p->vy += 0.0012f * dt * (float)(ft_rand() % 100 - 50);
		p->vx *= 1.0f - 0.015f * dt;
		p->vy *= 1.0f - 0.015f * dt;
	}
}

void	apply_particle_physics(t_particle *p, t_particle_type type, float dt)
{
	if (type == PARTICLE_SNOW || type == PARTICLE_RAIN)
		phys_fall(p, type, dt);
	else if (type == PARTICLE_FIRE || type == PARTICLE_SMOKE
		|| type == PARTICLE_BUBBLES)
		phys_rise(p, type, dt);
	else
		phys_misc(p, type, dt);
}

/*
 * Weather types respawn at the top when they leave the frame (or get
 * swallowed by the black hole), keeping the field dense.
 */
int	weather_recycle(t_particle *p, t_particle_type type, int force)
{
	void	(**tbl)(t_particle *p);

	if (type != PARTICLE_SNOW && type != PARTICLE_RAIN)
		return (0);
	if (!force && p->y <= (float)gviewport()->h + 20.0f
		&& p->x >= -60.0f && p->x <= (float)gviewport()->w + 60.0f)
		return (0);
	tbl = ps_init_tbl();
	tbl[type](p);
	p->lifetime = (float)(PARTICLE_LIFETIME + (ft_rand() % 100));
	p->life0 = p->lifetime;
	return (1);
}
