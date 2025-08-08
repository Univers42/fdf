/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rain.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:06:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:41:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	particle_rain(t_particle *p)
{
	p->x = (float)(rand() % WIN_WIDTH);
	p->y = -10.0f;
	p->z = (float)(rand() % 100 - 50);
	p->vx = (rand() % 40 - 20) * 0.2f;
	p->vy = 5.0f + (rand() % 30) * 0.2f;
	p->vz = 0.0f;
	p->size = 2.0f;
	p->color = 0x4080FF;
}
