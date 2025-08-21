/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_to_quat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:04:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:19:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/*
 *  Given an axis and angle, compute quaternion.
 */
void	axis_to_quat(float a[3], float phi, float q[4])
{
	vcopy(a, q);
	vnormal(q);
	vscale(q, sin(phi / 2.0));
	q[3] = cos(phi / 2.0);
}
