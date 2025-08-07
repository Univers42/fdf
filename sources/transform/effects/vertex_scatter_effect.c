/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_scatter_effect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 22:57:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static void	init_noise_offsets(float **noise_offsets)
{
	int	i;

	if (!*noise_offsets)
	{
		*noise_offsets = malloc(sizeof(float) * g_obj_effects.total_points);
		if (!*noise_offsets)
			return ;
		i = 0;
		while (i < g_obj_effects.total_points)
		{
			(*noise_offsets)[i] = (float)rand() / (float)RAND_MAX;
			i++;
		}
	}
}

static void	apply_scatter_to_points(t_app *fdf, float *noise_offsets)
{
	int		y;
	int		x;
	int		index;
	float	scatter;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			scatter = sinf(g_obj_effects.time_accumulator * 2.0f
					+ noise_offsets[index] * M_PI * 2.0f);
			scatter *= 25.0f * g_obj_effects.intensity;
			fdf->points[index] = g_obj_effects.original_points[index] + scatter;
			x++;
		}
		y++;
	}
}

void	apply_vertex_scatter_effect(t_app *fdf)
{
	static float	*noise_offsets = NULL;

	if (!g_obj_effects.original_points)
		return ;
	init_noise_offsets(&noise_offsets);
	if (!noise_offsets)
		return ;
	apply_scatter_to_points(fdf, noise_offsets);
}
