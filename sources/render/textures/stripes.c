/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:25:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:32:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	stripe_color(int id)
{
	if (id == 0)
		return (0xFF0000);
	if (id == 1)
		return (0x00FF00);
	return (0x0000FF);
}

static void	stripe_row(t_app *fdf, float w, int y)
{
	const t_texture_system	*t;
	int						x;

	t = gtexture(NULL);
	x = 0;
	while (x < fdf->width)
	{
		fdf->color[y * fdf->width + x] = blend_colors(
				t->original_colors[y * fdf->width + x],
				stripe_color(
					((int)((x + y + t->time_accumulator * 20.0f) / w)) % 3),
				0.5f);
		++x;
	}
}

void	apply_stripes_texture(t_app *fdf)
{
	const t_texture_system	*t = gtexture(NULL);
	int						y;
	float					stripe_width;

	stripe_width = 6.0f / t->scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		stripe_row(fdf, stripe_width, y);
		++y;
	}
}
