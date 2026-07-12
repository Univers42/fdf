/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoke.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Soft plumes that swell and thin as they climb. */
void	particle_smoke(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = vp->w * 0.5f + (float)(ft_rand() % (vp->w / 4))
		- vp->w / 8.0f;
	p->y = (float)vp->h - (float)(ft_rand() % 40);
	p->vx = 0.0f;
	p->vy = -(0.7f + 0.1f * (float)(ft_rand() % 10));
	p->vz = 0.0f;
	p->size = 6.0f + (float)(ft_rand() % 8);
	p->color = 0x8A8A96;
}
