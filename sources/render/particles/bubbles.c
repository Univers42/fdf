/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubbles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_rand(void);

/* Translucent bubbles wobbling up from the bottom. */
void	particle_bubbles(t_particle *p)
{
	t_viewport	*vp;

	vp = gviewport();
	p->x = (float)(ft_rand() % vp->w);
	p->y = (float)vp->h + (float)(ft_rand() % 80);
	p->vx = 0.0f;
	p->vy = -(0.8f + 0.1f * (float)(ft_rand() % 15));
	p->vz = 0.0f;
	p->size = 3.0f + (float)(ft_rand() % 6);
	p->color = 0x9FD8F0;
}
