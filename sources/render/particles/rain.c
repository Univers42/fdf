/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Fast slanted drops, rendered as motion streaks. */
void	particle_rain(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = (float)(ft_rand() % (vp->w + 600)) - 300.0f;
	p->y = -(float)(ft_rand() % 300) - 10.0f;
	if (ft_rand() % 3 == 0)
		p->y = (float)(ft_rand() % vp->h);
	p->vx = 1.6f * p->z;
	p->vy = (14.0f + 0.1f * (float)(ft_rand() % 60)) * p->z;
	p->vz = 0.0f;
	p->size = 2.0f;
	p->color = 0x9FB8D8;
}
