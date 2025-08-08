/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubbles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:42:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void	particle_bubbles(t_particle *p)
{
	p->x = (float)(rand() % WIN_WIDTH);
	p->y = (float)(WIN_HEIGHT + 10);
	p->z = (float)(rand() % 100 - 50);
	p->vx = (rand() % 20 - 10) * 0.2f;
	p->vy = -(1.0f + (rand() % 20) * 0.1f);
	p->vz = 0.0f;
	p->size = 3.0f + (rand() % 5);
	p->color = 0x80FFFF;
}
