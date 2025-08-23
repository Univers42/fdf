/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoke.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 17:57:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

// custom RNG API
int  ft_rand(void);

void	particle_smoke(t_particle *p)
{
	p->x = (float)(WIN_WIDTH / 2 + ft_rand() % 100 - 50);
	p->y = (float)(WIN_HEIGHT - 50 + ft_rand() % 50);
	p->z = (float)(ft_rand() % 100 - 50);
	p->vx = (ft_rand() % 40 - 20) * 0.2f;
	p->vy = -(1.0f + (ft_rand() % 20) * 0.1f);
	p->vz = (ft_rand() % 20 - 10) * 0.1f;
	p->size = 4.0f + (ft_rand() % 6);
	p->color = 0x404040;
}
