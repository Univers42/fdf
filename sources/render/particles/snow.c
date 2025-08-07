/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:10:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void    particle_snow(t_particle *p)
{
    p->x = (float)(rand() % WIN_WIDTH);
    p->y = -10.0f;
    p->z = (float)(rand() % 100 - 50);
    p->vx = (rand() % 20 - 10) * 0.1f;
    p->vy = 2.0f + (rand() % 20) * 0.1f;
    p->vz = 0.0f;
    p->size = 3.0f + (rand() % 3);
    p->color = 0xFFFFFF;
}