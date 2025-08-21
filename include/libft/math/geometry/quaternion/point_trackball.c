/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_trackball.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:24 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:31:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

// Apply 3x3 matrix transformation to a point
void	apply_trackball_matrix(float m[3][3], t_point *point)
{
	float	x;
	float	y;
	float	z;

	x = point->axis[X];
	y = point->axis[Y];
	z = point->axis[Z];
	point->axis[X] = m[0][0] * x + m[0][1] * y + m[0][2] * z;
	point->axis[Y] = m[1][0] * x + m[1][1] * y + m[1][2] * z;
	point->axis[Z] = m[2][0] * x + m[2][1] * y + m[2][2] * z;
}
