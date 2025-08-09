/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:20:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 15:19:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/* apply-table wrapped in a singleton-style accessor */
static void	(**tex_apply_tbl(void))(t_app *fdf)
{
	static void	(*tbl[TEXTURE_COUNT])(t_app *fdf) = {
		NULL,
		apply_checkerboard_texture,		/* 1 */
		apply_stripes_texture,			/* 2 */
		apply_wood_grain_texture,		/* 3 */
		apply_metal_brushed_texture,	/* 4 */
		apply_carbon_fiber_texture,		/* 5 */
		apply_marble_texture,			/* 6 */
		apply_brick_texture,			/* 7 */
		apply_circuit_board_texture,	/* 8 */
		apply_scales_texture,			/* 9 */
		apply_hexagon_texture,			/* 10 */
		apply_plasma_texture			/* 11 */
	};

	return (tbl);
}

/* short names for debug/print (singleton-style accessor) */
const char	**tex_name_tbl(void)
{
	static const char	*names[TEXTURE_COUNT] = {
		"None",
		"Checkerboard",
		"Stripes",
		"Wood",
		"Metal",
		"Carbon",
		"Marble",
		"Brick",
		"Circuit",
		"Scales",
		"Hexagon",
		"Plasma"
	};

	return (names);
}

static void	tex_apply_current(t_app *fdf, t_texture_system *t)
{
	void	(**tbl)(t_app *fdf);
	int		idx;

	tbl = tex_apply_tbl();
	idx = (int)t->current_texture;
	if (idx > (int)TEXTURE_NONE && idx < (int)TEXTURE_COUNT
		&& tbl[idx] != NULL)
		tbl[idx](fdf);
}

static void	tex_debug(const t_texture_system *t)
{
	static int		counter = 0;
	const char		**names;
	int				idx;

	counter++;
	if (counter % 300 != 0)
		return ;
	names = tex_name_tbl();
	idx = (int)t->current_texture;
	ft_printf("Texture %s (sc %.1f sp %.1f)\n",
		names[idx], t->scale_factor, t->animation_speed);
}

void	texture_system_update(t_app *fdf)
{
	t_texture_system	*t;

	t = gtexture(NULL);
	if (t->current_texture == TEXTURE_NONE)
		return ;
	store_original_texture_colors(fdf);
	if (!t->original_colors)
		return ;
	t->time_accumulator += 0.05f * t->animation_speed;
	tex_apply_current(fdf, t);
	tex_debug(t);
}
