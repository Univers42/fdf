/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:04:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 17:57:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

// custom RNG API
int  ft_rand(void);

void	particle_fire(t_particle *p)
{
	p->x = (float)(WIN_WIDTH / 2 + ft_rand() % 200 - 100);
	p->y = (float)(WIN_HEIGHT - 50);
	p->z = (float)(ft_rand() % 50);
	p->vx = (ft_rand() % 40 - 20) * 0.3f;
	p->vy = -(3.0f + (ft_rand() % 30) * 0.2f);
	p->vz = (ft_rand() % 20 - 10) * 0.1f;
	p->size = 4.0f + (ft_rand() % 4);
	if (ft_rand() % 2)
		p->color = 0xFF4400;
	else
		p->color = 0xFF4400;
}
