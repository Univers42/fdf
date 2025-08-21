/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_orthographic.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:13:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:19:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	orto_projection(t_point *points, t_point *projection, int len)
{
	int	i;

	if (points == NULL || projection == NULL || len <= 0)
		return ;
	i = 0;
	while (i < len)
	{
		projection[i] = points[i];
		i++;
	}
}
