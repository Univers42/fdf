/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:09:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:10:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void    particle_stars(t_particle *p)
{
    p->x = (float)(rand() % WIN_WIDTH);
	p->y = (float)(rand() % WIN_HEIGHT);
	p->z = (float)(rand() % 200 - 100);
	p->vx = (rand() % 10 - 5) * 0.1f;
	p->vy = (rand() % 10 - 5) * 0.1f;
	p->vz = 0.0f;
	p->size = 2.0f + (rand() % 3);
	p->color = 0xFFFFFF;
	p->lifetime = 400 + (rand() % 200);
}