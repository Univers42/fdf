/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:37:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:24:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/*
** Multiplies two quaternions: out = a * b.
** Usage: quat_mult(&out, &a, &b);
** Expects: All pointers are valid and non-NULL.
*/
void	quat_mult(t_quat *out, const t_quat *a, const t_quat *b)
{
	out->w = (a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z);
	out->x = (a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y);
	out->y = (a->w * b->y - a->x * b->z + a->y * b->w + a->z * b->x);
	out->z = (a->w * b->z + a->x * b->y - a->y * b->x + a->z * b->w);
}
