/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:08:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:09:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void    particle_sparks(t_particle *p)
{
    p->x = (float)(WIN_WIDTH / 2 + rand() % 100 - 50);
	p->y = (float)(WIN_HEIGHT / 2 + rand() % 100 - 50);
	p->z = (float)(rand() % 100 - 50);
	p->vx = (rand() % 100 - 50) * 0.6f;
	p->vy = (rand() % 100 - 50) * 0.6f;
	p->vz = (rand() % 40 - 20) * 0.2f;
	p->size = 2.0f + (rand() % 3);
	p->color = 0xFFFF00;
	p->lifetime = 80 + (rand() % 40);
}