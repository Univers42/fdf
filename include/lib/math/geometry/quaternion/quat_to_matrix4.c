/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_to_matrix4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 20:07:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:59:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Convert quaternion to 4x4 matrix
void	quaternion_to_matrix4(float q[4], float m[16])
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = q[0];
	y = q[1];
	z = q[2];
	w = q[3];
	m[0] = 1.0f - 2.0f * (y * y + z * z);
	m[1] = 2.0f * (x * y - z * w);
	m[2] = 2.0f * (x * z + y * w);
	m[3] = 0.0f;
	m[4] = 2.0f * (x * y + z * w);
	m[5] = 1.0f - 2.0f * (x * x + z * z);
	m[6] = 2.0f * (y * z - x * w);
	m[7] = 0.0f;
	m[8] = 2.0f * (x * z - y * w);
	m[9] = 2.0f * (y * z + x * w);
	m[10] = 1.0f - 2.0f * (x * x + y * y);
	m[11] = 0.0f;
	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;
}
