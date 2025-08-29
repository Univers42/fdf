/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:52:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 22:52:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	matrix4_dot_product(const float *m, float *v, float *out)
{
	int	x;
	int	y;

	y = 0;
	ft_memset(out, 0, sizeof(float [4]));
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			out[y] += m[y * 4 + x] * v[x];
			++x;
		}
		++y;
	}
}
