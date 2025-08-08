/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:04:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:43:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	particle_fire(t_particle *p)
{
	p->x = (float)(WIN_WIDTH / 2 + rand() % 200 - 100);
	p->y = (float)(WIN_HEIGHT - 50);
	p->z = (float)(rand() % 50);
	p->vx = (rand() % 40 - 20) * 0.3f;
	p->vy = -(3.0f + (rand() % 30) * 0.2f);
	p->vz = (rand() % 20 - 10) * 0.1f;
	p->size = 4.0f + (rand() % 4);
	if (rand() % 2)
		p->color = 0xFF4400;
	else
		p->color = 0xFF4400;
}
