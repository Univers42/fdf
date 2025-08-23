/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_particle1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:57:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 18:47:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// forward decls for RNG API (no public header provided)
int		ft_rand(void);
void	ft_srand(unsigned int new_seed, int select);

/* initializer dispatch table (index must match t_particle_type enum) */
void	(**ps_init_tbl(void))(t_particle *p)
{
	static void	(*tbl[PARTICLE_COUNT])(t_particle *p) = {
		NULL,
		particle_snow,
		particle_rain,
		particle_fire,
		particle_sparks,
		particle_stars,
		particle_bubbles,
		particle_dust,
		particle_smoke
	};

	return (tbl);
}

const int	*ps_rate_tbl(void)
{
	static const int	rate[PARTICLE_COUNT] = {
		3, /* NONE */
		4, /* SNOW */
		8, /* RAIN */
		6, /* FIRE */
		5, /* SPARKS */
		3, /* STARS */
		3, /* BUBBLES */
		3, /* DUST */
		3 /* SMOKE */
	};

	return (rate);
}

void	init_particle(t_particle *p, t_particle_type type, t_app *fdf)
{
	static int	seeded;
	void		(**tbl)(t_particle *p);

	(void)fdf;
	if (!seeded)
	{
		ft_srand((unsigned int)ft_time(), RNG_XORSHIFT);
		seeded = 1;
	}
	p->active = true;
	p->lifetime = PARTICLE_LIFETIME + (ft_rand() % 100);
	tbl = ps_init_tbl();
	if (type > PARTICLE_NONE && type < PARTICLE_COUNT && tbl[type] != NULL)
		tbl[type](p);
	else
		p->active = false;
}

void	apply_particle_physics(t_particle *p, t_particle_type type)
{
	if (type == PARTICLE_FIRE || type == PARTICLE_SMOKE)
	{
		p->vy -= 0.1f;
		p->size *= 0.998f;
	}
	else if (type == PARTICLE_SPARKS)
	{
		p->vy += 0.2f;
		p->size *= 0.995f;
	}
	else if (type == PARTICLE_BUBBLES)
		p->vy -= 0.05f;
	else if (type == PARTICLE_DUST)
	{
		p->vx *= 0.999f;
		p->vy *= 0.999f;
	}
}

void	update_particle(t_particle *p, t_particle_type type)
{
	if (!p->active)
		return ;
	p->x += p->vx;
	p->y += p->vy;
	p->z += p->vz;
	apply_particle_physics(p, type);
	p->lifetime--;
	if (p->lifetime <= 0)
		p->active = false;
	if (p->x < -50 || p->x > WIN_WIDTH + 50
		|| p->y < -50 || p->y > WIN_HEIGHT + 50)
		p->active = false;
}
