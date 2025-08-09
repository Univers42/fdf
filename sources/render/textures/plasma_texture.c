/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plasma_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:31:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	plasma_color(float t)
{
	if (t < 0.33f)
		return (blend_colors(0x0000FF, 0x00FFFF, t * 3.0f));
	if (t < 0.66f)
		return (blend_colors(0x00FFFF, 0xFFFF00,
				(t - 0.33f) * 3.0f));
	return (blend_colors(0xFFFF00, 0xFF0000,
			(t - 0.66f) * 3.0f));
}

static void	plasma_waves(t_plasma_vars *v)
{
	const t_texture_system	*t = gtexture(NULL);

	v->p1 = sinf((v->nx * 8.0f + t->time_accumulator * 2.0f) * M_PI);
	v->p2 = sinf((v->ny * 6.0f + t->time_accumulator * 1.5f) * M_PI);
	v->p3 = sinf(((v->nx + v->ny) * 10.0f + t->time_accumulator * 3.0f) * M_PI);
	v->p4 = sinf((sqrtf(v->nx * v->nx + v->ny * v->ny) * 12.0f
				- t->time_accumulator * 4.0f) * M_PI);
	v->intensity = (v->p1 + v->p2 + v->p3 + v->p4) / 4.0f;
	v->intensity = (v->intensity + 1.0f) / 2.0f;
}

static uint32_t	plasma_pixel(int x, int y, t_app *fdf)
{
	t_plasma_vars	v;

	v.nx = (float)x / fdf->width;
	v.ny = (float)y / fdf->height;
	plasma_waves(&v);
	return (plasma_color(v.intensity));
}

static void	plasma_row(t_app *fdf, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	int						x;
	int						idx;
	uint32_t				tc;

	x = 0;
	while (x < fdf->width)
	{
		idx = y * fdf->width + x;
		tc = plasma_pixel(x, y, fdf);
		fdf->color[idx] = blend_colors(t->original_colors[idx], tc, 0.8f);
		++x;
	}
}

void	apply_plasma_texture(t_app *fdf)
{
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		plasma_row(fdf, y);
		++y;
	}
}
