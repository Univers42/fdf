/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dust.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:03:10 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 17:58:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

// custom RNG API
int  ft_rand(void);

void	particle_dust(t_particle *p)
{
	p->x = (float)(ft_rand() % WIN_WIDTH);
	p->y = (float)(ft_rand() % WIN_HEIGHT);
	p->z = (float)(ft_rand() % 50 - 25);
	p->vx = (ft_rand() % 30 - 15) * 0.1f;
	p->vy = (ft_rand() % 30 - 15) * 0.1f;
	p->vz = (ft_rand() % 10 - 5) * 0.05f;
	p->size = 1.0f;
	p->color = 0x8B7355;
	p->lifetime = 500 + (ft_rand() % 200);
}
