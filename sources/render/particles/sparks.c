/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Ballistic embers bursting up in a cone; they bounce on the ground. */
void	particle_sparks(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = vp->w * 0.5f + (float)(ft_rand() % 200) - 100.0f;
	p->y = (float)vp->h - 30.0f;
	p->vx = 0.1f * (float)(ft_rand() % 140 - 70);
	p->vy = -(6.0f + 0.1f * (float)(ft_rand() % 90));
	p->vz = 0.0f;
	p->size = 1.0f + (float)(ft_rand() % 2);
	p->color = 0xFFD27A;
	p->lifetime = (float)(120 + ft_rand() % 90);
	p->life0 = p->lifetime;
}
