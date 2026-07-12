/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Wind-blown flakes drifting from above; layer depth in z. */
void	particle_snow(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = (float)(ft_rand() % (vp->w + 400)) - 200.0f;
	p->y = -(float)(ft_rand() % 200) - 10.0f;
	if (ft_rand() % 3 == 0)
		p->y = (float)(ft_rand() % vp->h);
	p->vx = 0.35f;
	p->vy = (1.0f + 0.1f * (float)(ft_rand() % 15)) * p->z;
	p->vz = 0.0f;
	p->size = 2.0f + (float)(ft_rand() % 3);
	p->color = 0xF2F6FF;
}
