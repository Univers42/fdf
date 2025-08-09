/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:28:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 14:40:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "ft_math.h"

#define TRANSITION_FRAMES 60
#define SHAPE_COUNT 11

/* helpers to keep functions short and declarations at top */

static int	ensure_original_buffer(t_app *fdf, t_transition_state *st)
{
	size_t	total;

	total = (size_t)fdf->width * (size_t)fdf->height * 3u;
	if (st->original_positions)
		free(st->original_positions);
	st->original_positions = (float *)malloc(sizeof(float) * total);
	if (!st->original_positions)
		return (0);
	return (1);
}

static void	fill_original_positions(t_app *fdf, t_transition_state *st)
{
	int	y;
	int	x;
	int	index;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			st->original_positions[index * 3 + 0] = (float)x;
			st->original_positions[index * 3 + 1] = (float)y;
			st->original_positions[index * 3 + 2] = fdf->points[index];
			++x;
		}
		++y;
	}
}

/* Store original grid positions once */
void	store_original_positions(t_app *fdf)
{
	t_transition_state	*st;

	st = gtransition(NULL);
	if (st->initialized)
		return ;
	if (!ensure_original_buffer(fdf, st))
		return ;
	fill_original_positions(fdf, st);
	st->initialized = true;
}

static void	apply_row(t_app *fdf, t_transition_state *st, float t, int y)
{
	t_row_apply	v;
	t_point2	p;

	v.x = 0;
	while (v.x < fdf->width)
	{
		v.index = y * fdf->width + v.x;
		p.x = v.x;
		p.y = y;
		get_shape_position(st->current_shape, fdf, &p, &v.c);
		get_shape_position(st->target_shape, fdf, &p, &v.d);
		v.o.x = v.c.x + (v.d.x - v.c.x) * t;
		v.o.y = v.c.y + (v.d.y - v.c.y) * t;
		v.o.z = v.c.z + (v.d.z - v.c.z) * t;
		v.sp[0] = v.o.x;
		v.sp[1] = v.o.y;
		v.sp[2] = v.o.z;
		v.sp[3] = 1.0f;
		v.dp = (float *)&fdf->transformed_points[v.index];
		matrix4_dot_product(fdf->trans_stack.combined, v.sp, v.dp);
		++v.x;
	}
}

static void	apply_interpolated_frame(t_app *fdf, t_transition_state *st, float t)
{
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		apply_row(fdf, st, t, y);
		++y;
	}
}

void	transition_update(t_app *fdf)
{
	t_transition_state	*st;
	float				progress;
	float				smooth_t;

	st = gtransition(NULL);
	if (!st->active && st->current_shape == SHAPE_ORIGINAL)
		return ;
	store_original_positions(fdf);
	if (!st->original_positions)
		return ;
	if (st->active)
	{
		progress = (float)st->frame / (float)st->max_frames;
		smooth_t = ease_in_out(progress);
		apply_interpolated_frame(fdf, st, smooth_t);
		st->frame++;
		if (st->frame >= st->max_frames)
		{
			st->active = false;
			st->frame = 0;
			st->current_shape = st->target_shape;
		}
	}
	else if (st->current_shape != SHAPE_ORIGINAL)
		apply_shape_with_transform(fdf, st->current_shape);
}

void	transition_start_torus(bool to_torus)
{
	t_transition_state	*st;
	t_shape_type		 next;

	(void)to_torus;
	st = gtransition(NULL);
	next = (st->current_shape + 1) % SHAPE_COUNT;
	st->active = true;
	st->frame = 0;
	st->target_shape = next;
}

bool	transition_is_active(void)
{
	t_transition_state	*st;

	st = gtransition(NULL);
	return (st->active || st->current_shape != SHAPE_ORIGINAL);
}

/* Singleton accessor for transition state */
t_transition_state	*gtransition(t_transition_state *set)
{
	static t_transition_state	instance = {0};
	static bool					initialized = false;

	if (set)
		instance = *set;
	if (!initialized)
	{
		instance.frame = 0;
		instance.max_frames = TRANSITION_FRAMES;
		instance.active = false;
		instance.current_shape = SHAPE_ORIGINAL;
		instance.target_shape = SHAPE_ORIGINAL;
		instance.original_positions = NULL;
		instance.initialized = false;
		initialized = true;
	}
	return (&instance);
}

// Wrapper kept for compatibility with event code
void	transition_start_shape_cycle(t_app *fdf)
{
	(void)fdf;
	transition_start_torus(false);
}

// Wrapper kept for compatibility with render loop
bool	transition_app_is_active(t_app *fdf)
{
	(void)fdf;
	return (transition_is_active());
}

void	transition_cleanup(t_app *fdf)
{
	t_transition_state	*st;

	(void)fdf;
	st = gtransition(NULL);
	if (st->original_positions)
	{
		free(st->original_positions);
		st->original_positions = NULL;
	}
	st->initialized = false;
	st->active = false;
	st->frame = 0;
	st->current_shape = SHAPE_ORIGINAL;
	st->target_shape = SHAPE_ORIGINAL;
}
