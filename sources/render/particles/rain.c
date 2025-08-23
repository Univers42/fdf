/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rain.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:06:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 18:38:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

int	ft_rand(void);

void	particle_rain(t_particle *p)
{
	p->x = (float)(ft_rand() % WIN_WIDTH);
	p->y = -10.0f;
	p->z = (float)(ft_rand() % 100 - 50);
	p->vx = (ft_rand() % 40 - 20) * 0.2f;
	p->vy = 5.0f + (ft_rand() % 30) * 0.2f;
	p->vz = 0.0f;
	p->size = 2.0f;
	p->color = 0x4080FF;
}
