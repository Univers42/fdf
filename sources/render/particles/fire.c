/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Flames rise from a hearth band at the bottom center. */
void	particle_fire(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = vp->w * 0.5f + (float)(ft_rand() % (vp->w / 3))
		- vp->w / 6.0f;
	p->y = (float)vp->h - (float)(ft_rand() % 60);
	p->vx = 0.06f * (float)(ft_rand() % 20 - 10);
	p->vy = -(1.5f + 0.1f * (float)(ft_rand() % 25));
	p->vz = 0.0f;
	p->size = 4.0f + (float)(ft_rand() % 6);
	p->color = 0xFFCE70;
	p->lifetime = (float)(90 + ft_rand() % 70);
	p->life0 = p->lifetime;
}
