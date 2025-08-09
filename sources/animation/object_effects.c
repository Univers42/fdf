/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:38:38 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:16:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

/* function table wrapped in a singleton-style accessor */
static void	(**obj_effect_fn(void))(t_app *fdf)
{
	static void	(*tbl[OBJECT_EFFECT_COUNT])(t_app *fdf) = {
		NULL, /* OBJ_EFFECT_NONE */
		apply_vertex_wave_effect,
		apply_geometric_pulse_effect,
		apply_vertex_explosion_effect,
		apply_spiral_twist_effect,
		apply_depth_distortion_effect,
		apply_vertex_magnet_effect,
		apply_geometric_fold_effect,
		apply_height_oscillation_effect,
		apply_vertex_scatter_effect
	};

	return (tbl);
}

static void	oe_apply_current(t_app *fdf, const t_object_effects_system *oe)
{
	int			idx;
	void		(**tbl)(t_app *fdf);

	idx = (int)oe->current_effect;
	if (idx < 0 || idx >= OBJECT_EFFECT_COUNT)
		return ;
	tbl = obj_effect_fn();
	if (tbl[idx] != NULL)
		tbl[idx](fdf);
}

/* Store original point positions */
void	store_original_object_points(t_app *fdf)
{
	t_object_effects_system	*oe;
	int						i;

	oe = gobjfx(NULL);
	if (oe->initialized)
		return ;
	oe->total_points = fdf->width * fdf->height;
	if (oe->original_points)
		free(oe->original_points);
	oe->original_points = malloc(sizeof(float) * oe->total_points);
	if (!oe->original_points)
		return ;
	i = 0;
	while (i < oe->total_points)
	{
		oe->original_points[i] = fdf->points[i];
		++i;
	}
	oe->initialized = true;
}

void	object_effects_update(t_app *fdf)
{
	t_object_effects_system	*oe;

	oe = gobjfx(NULL);
	if (oe->current_effect == OBJ_EFFECT_NONE)
		return ;
	store_original_object_points(fdf);
	if (!oe->original_points)
		return ;
	oe->time_accumulator += WAVE_FREQUENCY;
	oe_apply_current(fdf, oe);
}

void	transition_start_object_effects(bool to_effects)
{
	t_object_effects_system		*oe;
	t_object_effect_type		next;

	(void)to_effects;
	oe = gobjfx(NULL);
	next = (oe->current_effect + 1) % OBJECT_EFFECT_COUNT;
	oe->current_effect = next;
	oe->time_accumulator = 0.0f;
}
