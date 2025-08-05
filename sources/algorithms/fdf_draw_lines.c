/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:31:39 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/05 18:28:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline bool	should_clip(t_point4 *p1, t_point4 *p2)
{
	return ((p1->x < -1 && p2->x < -1)
		|| (p1->x > 1 && p2->x > 1)
		|| (p1->y < -1 && p2->y < -1)
		|| (p1->y > 1 && p2->y > 1)
		|| (p1->z < -1 && p2->z < -1)
		|| (p1->z > 1 && p2->z > 1));
}

/*
 * Stride downscales on zoom out and test in clips points.
 */
void	fdf_draw_lines(t_app *f)
{
	size_t	i;

	i = 0;
	while (i < f->n_edges)
	{
		if (should_clip(&f->transformed_points[f->edges[i][0]],
			&f->transformed_points[f->edges[i][1]]))
		{
			++i;
			continue ;
		}
		bresenham_init(&f->bresenham_state, f, i);
		if (f->bresenham_state.delta[0] >= f->bresenham_state.delta[1])
			draw_line_x_major(&f->bresenham_state,
				(unsigned int *)f->renderer.data);
		else
			draw_line_y_major(&f->bresenham_state,
				(unsigned int *)f->renderer.data);
		++i;
	}
}
