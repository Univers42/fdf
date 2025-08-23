/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 17:57:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

// custom RNG API
int  ft_rand(void);

void	particle_snow(t_particle *p)
{
	p->x = (float)(ft_rand() % WIN_WIDTH);
	p->y = -10.0f;
	p->z = (float)(ft_rand() % 100 - 50);
	p->vx = (ft_rand() % 20 - 10) * 0.1f;
	p->vy = 2.0f + (ft_rand() % 20) * 0.1f;
	p->vz = 0.0f;
	p->size = 3.0f + (ft_rand() % 3);
	p->color = 0xFFFFFF;
}
