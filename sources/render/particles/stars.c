/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:09:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 17:57:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

// custom RNG API
int  ft_rand(void);

void	particle_stars(t_particle *p)
{
	p->x = (float)(ft_rand() % WIN_WIDTH);
	p->y = (float)(ft_rand() % WIN_HEIGHT);
	p->z = (float)(ft_rand() % 200 - 100);
	p->vx = (ft_rand() % 10 - 5) * 0.1f;
	p->vy = (ft_rand() % 10 - 5) * 0.1f;
	p->vz = 0.0f;
	p->size = 2.0f + (ft_rand() % 3);
	p->color = 0xFFFFFF;
	p->lifetime = 400 + (ft_rand() % 200);
}
