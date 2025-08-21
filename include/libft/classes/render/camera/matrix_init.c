/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:42:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:10:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	matrix_init(float (*matrix)[3])
{
	int	x;
	int	y;

	x = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			matrix[x][y] = 0;
			y++;
		}
		x++;
	}
}

void	quaternion_init(float (*matrix)[4])
{
	int	x;
	int	y;

	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (x == y)
				matrix[x][y] = 1.0f;
			else
				matrix[x][y] = 0.0f;
			y++;
		}
		x++;
	}
}
