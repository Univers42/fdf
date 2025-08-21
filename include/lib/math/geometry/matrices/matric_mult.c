/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matric_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:37:50 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/03 15:55:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Multiplies two 4x4 matrices: out = a * b.
** Usage: matrix_mult(&out, &a, &b);
** Expects: All pointers are valid and non-NULL.
*/
void	matrix_mult(t_mat4 *out, const t_mat4 *a, const t_mat4 *b)
{
	t_mat4	res;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.m[i][j] = 0.0f;
			k = 0;
			while (k < 4)
			{
				res.m[i][j] += a->m[i][k] * b->m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	matrix_copy(out, &res);
}
