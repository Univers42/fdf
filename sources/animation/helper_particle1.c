/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_particle1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:57:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/26 12:24:15 by dlesieur         ###   ########.fr       */
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
		9, /* SNOW */
		15, /* RAIN */
		11, /* FIRE */
		6, /* SPARKS */
		5, /* STARS */
		4, /* BUBBLES */
		5, /* DUST */
		5 /* SMOKE */
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
	p->lifetime = (float)(PARTICLE_LIFETIME + (ft_rand() % 100));
	p->life0 = p->lifetime;
	p->phase = 0.01f * (float)(ft_rand() % 628);
	p->z = 0.4f + 0.01f * (float)(ft_rand() % 60);
	tbl = ps_init_tbl();
	if (type > PARTICLE_NONE && type < PARTICLE_COUNT && tbl[type] != NULL)
		tbl[type](p);
	else
		p->active = false;
}
