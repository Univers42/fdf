/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_scatter_effect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/26 12:24:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "libft.h"

/* forward decls for RNG API (no public header provided) */
int		ft_rand(void);
void	ft_srand(unsigned int new_seed, int select);

static void	vs_seed_once(void)
{
	static int	seeded;

	if (!seeded)
	{
		ft_srand((unsigned int)ft_time(), RNG_XORSHIFT);
		seeded = 1;
	}
}

static int	vs_ensure_noise(t_app *fdf, int total)
{
	size_t	req;

	if (total <= 0)
		return (0);
	req = (size_t)total * 3u;
	if (fdf->noise_offsets && fdf->noise_size == total)
		return (1);
	free(fdf->noise_offsets);
	fdf->noise_offsets = (float *)malloc(sizeof(float) * req);
	if (!fdf->noise_offsets)
		return (0);
	fdf->noise_size = total;
	return (1);
}

static void	vs_fill_noise(float *buf, int n3)
{
	int	i;

	vs_seed_once();
	i = 0;
	while (i < n3)
	{
		buf[i] = ((float)ft_rand() / (float)RAND_MAX) * 2.0f - 1.0f;
		++i;
	}
}

static void	vs_apply_point(
	t_app *fdf,
	const t_object_effects_system *oe,
	int i,
	float tf
)
{
	float	*no;
	float	inten;
	float	sum;

	no = fdf->noise_offsets;
	inten = oe->intensity;
	sum = no[i * 3] * tf
		+ no[i * 3 + 1] * 0.3f
		+ no[i * 3 + 2] * sinf(oe->time_accumulator * 2.0f) * 0.2f;
	fdf->points[i] = oe->original_points[i] + sum * inten;
}

void	apply_vertex_scatter_effect(t_app *fdf)
{
	const t_object_effects_system	*oe;
	int								total;
	int								i;
	float							tf;

	oe = gobjfx(NULL);
	if (!fdf || !oe || !fdf->points || !oe->original_points)
		return ;
	total = fdf->width * fdf->height;
	if (!vs_ensure_noise(fdf, total))
		return ;
	vs_fill_noise(fdf->noise_offsets, total * 3);
	tf = sinf(oe->time_accumulator) * 0.5f + 1.0f;
	i = 0;
	while (i < total)
	{
		vs_apply_point(fdf, oe, i, tf);
		++i;
	}
}
