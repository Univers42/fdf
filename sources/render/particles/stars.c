/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Static twinkling stars, denser toward the top of the frame. */
void	particle_stars(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = (float)(ft_rand() % vp->w);
	p->y = (float)(ft_rand() % vp->h);
	if (ft_rand() % 3)
		p->y *= 0.6f;
	p->vx = 0.0f;
	p->vy = 0.0f;
	p->vz = 0.0f;
	p->size = 1.0f + (float)(ft_rand() % 2);
	p->color = 0xFFFFFF;
	if (ft_rand() % 4 == 0)
		p->color = 0xAFC8FF;
	else if (ft_rand() % 5 == 0)
		p->color = 0xFFE2B0;
}
