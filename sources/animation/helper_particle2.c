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

void	draw_particle_square(uint32_t *screen, struct s_pdraw *d)
{
	int	dy;
	int	dx;
	int	x;
	int	y;

	dy = 0;
	while (dy < d->size)
	{
		dx = 0;
		while (dx < d->size)
		{
			x = d->px + dx;
			y = d->py + dy;
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				screen[y * WIN_WIDTH + x] = d->color;
			dx++;
		}
		dy++;
	}
}

void	render_particles(t_app *fdf)
{
	t_particle_transition	*ps;
	uint32_t				*screen;
	int						i;
	struct s_pdraw			d;

	ps = gparticles(NULL);
	screen = (uint32_t *)fdf->renderer.data;
	i = 0;
	while (i < MAX_PARTICLES)
	{
		if (ps->particles[i].active)
		{
			d.size = (int)ps->particles[i].size + 2;
			d.px = (int)ps->particles[i].x;
			d.py = (int)ps->particles[i].y;
			d.color = ps->particles[i].color;
			if (ps->current_type == PARTICLE_SNOW)
				d.color = 0xFFFFFF;
			draw_particle_square(screen, &d);
		}
		i++;
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
