/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:38:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:10:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Sets all elements of the 4x4 matrix to zero.
** Usage: matrix_zero(&mat);
** Expects: Pointer to a valid t_mat4.
*/
void	matrix_zero(t_mat4 *out)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out->m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
}
