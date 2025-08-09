/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:17:04 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:43:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	checker_row(t_app *fdf, float size, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	t_pos_check				pos;
	t_point2				c;
	int						is_white;
	uint32_t				tc;

	pos.x = -1;
	while (++pos.x < fdf->width)
	{
		pos.index = y * fdf->width + pos.x;
		c.x = (int)(pos.x / size);
		c.y = (int)(y / size);
		is_white = ((c.x + c.y) % 2) == 0;
		tc = is_white * 0xFFFFFF;
		fdf->color[pos.index] = blend_colors(t->original_colors[pos.index],
				tc, 0.6f);
	}
}

void	apply_checkerboard_texture(t_app *fdf)
{
	const t_texture_system	*t = gtexture(NULL);
	int						y;
	float					checker_size;

	checker_size = 8.0f / t->scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		checker_row(fdf, checker_size, y);
		++y;
	}
}
