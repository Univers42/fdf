/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:08:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 18:38:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

int	ft_rand(void);

void	particle_sparks(t_particle *p)
{
	p->x = (float)(WIN_WIDTH / 2 + ft_rand() % 100 - 50);
	p->y = (float)(WIN_HEIGHT / 2 + ft_rand() % 100 - 50);
	p->z = (float)(ft_rand() % 100 - 50);
	p->vx = (ft_rand() % 100 - 50) * 0.6f;
	p->vy = (ft_rand() % 100 - 50) * 0.6f;
	p->vz = (ft_rand() % 40 - 20) * 0.2f;
	p->size = 2.0f + (ft_rand() % 3);
	p->color = 0xFFFF00;
	p->lifetime = 80 + (ft_rand() % 40);
}
