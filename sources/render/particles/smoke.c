/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoke.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:42:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void	particle_smoke(t_particle *p)
{
	p->x = (float)(WIN_WIDTH / 2 + rand() % 100 - 50);
	p->y = (float)(WIN_HEIGHT - 50 + rand() % 50);
	p->z = (float)(rand() % 100 - 50);
	p->vx = (rand() % 40 - 20) * 0.2f;
	p->vy = -(1.0f + (rand() % 20) * 0.1f);
	p->vz = (rand() % 20 - 10) * 0.1f;
	p->size = 4.0f + (rand() % 6);
	p->color = 0x404040;
}
