/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:20:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 13:38:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h> /* atexit, free */

static void	tex_fade(t_app *fdf, t_texture_system *t);

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

static void	tex_apply_current(t_app *fdf, t_texture_system *t)
{
	void	(**tbl)(t_app *fdf);
	int		idx;

	tbl = tex_apply_tbl();
	idx = (int)t->current_texture;
	if (idx > (int)TEXTURE_NONE && idx < (int)TEXTURE_COUNT
		&& tbl[idx] != NULL)
		tbl[idx](fdf);
	tex_fade(fdf, t);
}

/* one-time cleanup registered at process exit to release snapshot */
static void	tex_cleanup_on_exit(void)
{
	t_texture_system	*t;

	t = gtexture(NULL);
	free(t->original_colors);
	t->original_colors = NULL;
	free(t->fade_from);
	t->fade_from = NULL;
}

/*
 * Crossfade: on texture switch the previous frame's colors are frozen
 * in fade_from, then blended over the incoming texture for ~24 frames.
 */
static void	tex_fade(t_app *fdf, t_texture_system *t)
{
	int	i;

	if (!t->fade_from)
		t->fade_from = (uint32_t *)malloc(sizeof(uint32_t)
				* fdf->width * fdf->height);
	if (t->fade_pending && t->fade_from)
	{
		ft_memcpy(t->fade_from, fdf->color,
			sizeof(uint32_t) * fdf->width * fdf->height);
		t->fade_left = 24;
		t->fade_pending = false;
	}
	if (t->fade_left <= 0)
		return ;
	i = fdf->width * fdf->height;
	while (i-- > 0)
		fdf->color[i] = lerp_color(fdf->color[i], t->fade_from[i],
				(float)t->fade_left / 24.0f);
	t->fade_left--;
}

/* capture the original colors only once to avoid repeated allocations */
void	texture_system_update(t_app *fdf)
{
	t_texture_system	*t;
	static int			cleanup_registered = 0;

	t = gtexture(NULL);
	if (t->current_texture == TEXTURE_NONE)
		return ;
	if (!t->original_colors)
	{
		store_original_texture_colors(fdf);
		if (!t->original_colors)
			return ;
		if (!cleanup_registered)
		{
			atexit(tex_cleanup_on_exit);
			cleanup_registered = 1;
		}
	}
	t->frame++;
	if (fdf->width * fdf->height > 400000 && (t->frame & 1))
		return ;
	t->time_accumulator += 0.05f * t->animation_speed;
	tex_apply_current(fdf, t);
}
