/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_scatter_effect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:55:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

// forward decl for accessor
t_object_effects_system *gobjfx(t_object_effects_system *set);

// RNG seed once
static void	seed_rng_once(void)
{
	static int	seeded = 0;

	if (!seeded)
	{
		srand(123456u); // deterministic; change to time(NULL) if you prefer
		seeded = 1;
	}
}

// Singleton buffer for per-vertex noise offsets [0..1)
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

static void	apply_scatter_to_points(t_app *fdf, float radius)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	const float						*offs = get_noise_offsets(fdf);
	int		y;
	int		x;
	int		index;
	float	scatter;
	float	base;
	float	angle;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			base = oe->time_accumulator * 2.0f;
			angle = base + (offs ? offs[index] : 0.0f) * M_PI * 2.0f;
			scatter = sinf(angle);
			scatter *= radius;
			fdf->points[index] = oe->original_points[index] + scatter;
			x++;
		}
		y++;
	}
}

void	apply_vertex_scatter_effect(t_app *fdf)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	float							radius;

	if (!oe->original_points)
		return ;
	radius = 10.0f + 15.0f * fabsf(sinf(oe->time_accumulator * 0.7f));
	radius *= oe->intensity;
	apply_scatter_to_points(fdf, radius);
}
