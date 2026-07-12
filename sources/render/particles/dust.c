/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dust.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Fine motes drifting on Brownian air currents. */
void	particle_dust(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = (float)(ft_rand() % vp->w);
	p->y = (float)(ft_rand() % vp->h);
	p->vx = 0.02f * (float)(ft_rand() % 20 - 10);
	p->vy = 0.02f * (float)(ft_rand() % 20 - 10);
	p->vz = 0.0f;
	p->size = 1.0f + (float)(ft_rand() % 2);
	p->color = 0xC9BFA8;
}
