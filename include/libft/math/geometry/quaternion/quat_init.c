/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:37:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:23:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/*
** Initializes a quaternion with the given components (x, y, z, w).
** Usage: quat_init(&q, x, y, z, w);
** Expects: q is a valid pointer.
*/
void	quat_init(t_quat *q, t_fpoint4 p)
{
	q->x = p.x;
	q->y = p.y;
	q->z = p.z;
	q->w = p.w;
}
