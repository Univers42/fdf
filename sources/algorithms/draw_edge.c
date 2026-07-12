/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_edge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline bool	should_clip(t_fpoint4 *p1, t_fpoint4 *p2)
{
	return ((p1->x < -1 && p2->x < -1)
		|| (p1->x > 1 && p2->x > 1)
		|| (p1->y < -1 && p2->y < -1)
		|| (p1->y > 1 && p2->y > 1)
		|| (p1->z < -1 && p2->z < -1)
		|| (p1->z > 1 && p2->z > 1));
}

/*
 * Degenerate edge (both endpoints on the same pixel, the common case on
 * zoomed-out big maps): plot one pixel, skip the whole line setup.
 */
static inline void	plot_point(t_app *f, t_bresenham_state *b)
{
	if ((unsigned int)b->p1[0] < WIN_WIDTH
		&& (unsigned int)b->p1[1] < WIN_HEIGHT)
		((unsigned int *)f->renderer.data)[(long)b->p1[1] * WIN_WIDTH
			+ b->p1[0]] = b->color1;
}

static void	edge_rasterize(t_app *f)
{
	if ((f->bresenham_state.delta[0] | f->bresenham_state.delta[1]) == 0)
		plot_point(f, &f->bresenham_state);
	else if (f->bresenham_state.delta[0] >= f->bresenham_state.delta[1])
		draw_line_x_major(&f->bresenham_state,
			(unsigned int *)f->renderer.data);
	else
		draw_line_y_major(&f->bresenham_state,
			(unsigned int *)f->renderer.data);
}

void	draw_edge(t_app *f, int i0, int i1)
{
	t_fpoint4	a;
	t_fpoint4	b;

	a = f->transformed_points[i0];
	b = f->transformed_points[i1];
	f->bresenham_state.color1 = f->color[i0];
	f->bresenham_state.color2 = f->color[i1];
	if (gcam()->active)
	{
		if (!edge_project(&a, &b))
			return ;
		f->bresenham_state.color1 = fog_color(f->bresenham_state.color1,
				a.w, fmaxf(f->width, f->height));
		f->bresenham_state.color2 = fog_color(f->bresenham_state.color2,
				b.w, fmaxf(f->width, f->height));
	}
	if (should_clip(&a, &b))
		return ;
	bresenham_init(&f->bresenham_state, &a, &b);
	edge_rasterize(f);
}
