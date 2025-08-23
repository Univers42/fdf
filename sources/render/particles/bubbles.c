/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubbles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 17:58:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

// custom RNG API
int  ft_rand(void);

void	particle_bubbles(t_particle *p)
{
	p->x = (float)(ft_rand() % WIN_WIDTH);
	p->y = (float)(WIN_HEIGHT + 10);
	p->z = (float)(ft_rand() % 100 - 50);
	p->vx = (ft_rand() % 20 - 10) * 0.2f;
	p->vy = -(1.0f + (ft_rand() % 20) * 0.1f);
	p->vz = 0.0f;
	p->size = 3.0f + (ft_rand() % 5);
	p->color = 0x80FFFF;
}
