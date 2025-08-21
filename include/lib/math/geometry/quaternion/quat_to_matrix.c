/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_to_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:23:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:26:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

// Convert quaternion to 3x3 rotation matrix
void	quaternion_to_matrix(float q[4], float m[3][3])
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = q[0];
	y = q[1];
	z = q[2];
	w = q[3];
	m[0][0] = 1.0f - 2.0f * (y * y + z * z);
	m[0][1] = 2.0f * (x * y - z * w);
	m[0][2] = 2.0f * (x * z + y * w);
	m[1][0] = 2.0f * (x * y + z * w);
	m[1][1] = 1.0f - 2.0f * (x * x + z * z);
	m[1][2] = 2.0f * (y * z - x * w);
	m[2][0] = 2.0f * (x * z - y * w);
	m[2][1] = 2.0f * (y * z + x * w);
	m[2][2] = 1.0f - 2.0f * (x * x + y * y);
}
