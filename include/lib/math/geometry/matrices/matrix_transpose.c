/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:38:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:11:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Computes the transpose of a 4x4 matrix.
** Usage: matrix_transpose(&out, &in);
** Expects: Both pointers are valid and non-NULL.
*/

void	matrix_transpose(t_mat4 *out, const t_mat4 *in)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out->m[i][j] = in->m[j][i];
			j++;
		}
		i++;
	}
}
