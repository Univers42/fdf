/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dust.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:03:10 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:04:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void    particle_dust(t_particle *p)
{
    p->x = (float)(rand() % WIN_WIDTH);
	p->y = (float)(rand() % WIN_HEIGHT);
	p->z = (float)(rand() % 50 - 25);
	p->vx = (rand() % 30 - 15) * 0.1f;
	p->vy = (rand() % 30 - 15) * 0.1f;
	p->vz = (rand() % 10 - 5) * 0.05f;
	p->size = 1.0f;
	p->color = 0x8B7355;
	p->lifetime = 500 + (rand() % 200);
}