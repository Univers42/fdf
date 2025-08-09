/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_scatter_effect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:29:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

// forward decl for accessor
t_object_effects_system	*gobjfx(t_object_effects_system *set);

static void	seed_rng_once(void)
{
	static int	seeded = 0;

	if (!seeded)
	{
		srand(123456u);
		seeded = 1;
	}
}

static const float	*get_noise_offsets(t_app *fdf)
{
	static float	*buf = NULL;
	static int		sz = 0;
	int				n;
	int				i;

	n = fdf->width * fdf->height;
	if (n <= 0)
		return (NULL);
	if (buf == NULL || sz != n)
	{
		free(buf);
		buf = (float *)malloc(sizeof(float) * n);
		if (!buf)
			return (NULL);
		sz = n;
		seed_rng_once();
		i = -1;
		while (++i < n)
			buf[i] = (float)rand() / (float)RAND_MAX;
	}
	return (buf);
}

static float	scatter_at(
	const t_object_effects_system *oe, const float *offs, int index, float r)
{
	float	offv;
	float	val;

	offv = 0.0f;
	if (offs)
		offv = offs[index];
	val = sinf(
			oe->time_accumulator * 2.0f
			+ offv * (float)M_PI * 2.0f);
	return (val * r);
}

static void	apply_scatter_to_points(t_app *fdf, float radius)
{
	const t_object_effects_system	*oe;
	const float						*offs;
	t_point2						c;
	int								index;

	oe = gobjfx(NULL);
	offs = get_noise_offsets(fdf);
	c.y = 0;
	while (c.y < fdf->height)
	{
		c.x = 0;
		while (c.x < fdf->width)
		{
			index = c.y * fdf->width + c.x;
			fdf->points[index] = oe->original_points[index]
				+ scatter_at(oe, offs, index, radius);
			++c.x;
		}
		++c.y;
	}
}

void	apply_vertex_scatter_effect(t_app *fdf)
{
	const t_object_effects_system	*oe;
	float							radius;

	oe = gobjfx(NULL);
	if (!oe->original_points)
		return ;
	radius = 10.0f + 15.0f * fabsf(sinf(oe->time_accumulator * 0.7f));
	radius *= oe->intensity;
	apply_scatter_to_points(fdf, radius);
}
