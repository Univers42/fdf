/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:00:59 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:01:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

void	add_quats(float q1[4], float q2[4], float dest[4])
{
	static int	count = 0;
	float		t1[4];
	float		t2[4];
	float		t3[4];
	float		tf[4];

	vcopy(q1, t1);
	vscale(t1, q2[3]);
	vcopy(q2, t2);
	vscale(t2, q1[3]);
	vcross(q2, q1, t3);
	vadd(t1, t2, tf);
	vadd(t3, tf, tf);
	tf[3] = q1[3] * q2[3] - vdot(q1, q2);
	vcopy(tf, dest);
	if (++count > RENORMCOUNT)
	{
		count = 0;
		normalize_quat(dest);
	}
}
