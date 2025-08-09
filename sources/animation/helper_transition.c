/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:48:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 14:52:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* table is defined in position_shape1.c */
extern t_shape_pos_fn	*shape_pos_tbl(void);

static void	pos_fallback(t_app *fdf, t_point2 *p, t_fpoint3 *o)
{
	(void)fdf;
	if (!p || !o)
		return ;
	o->x = (float)p->x;
	o->y = (float)p->y;
	o->z = 0.0f;
}

void	get_shape_position(t_shape_type shape, t_app *fdf, t_point2 *p,
	t_fpoint3 *out)
{
	t_shape_pos_fn	*tbl;
	int				idx;
	int				index;

	if (!fdf || !p || !out || fdf->width <= 1 || fdf->height <= 1)
		return (pos_fallback(fdf, p, out));
	index = p->y * fdf->width + p->x;
	if (index < 0 || index >= fdf->width * fdf->height)
		return (pos_fallback(fdf, p, out));
	tbl = shape_pos_tbl();
	if (!tbl)
		return (pos_fallback(fdf, p, out));
	idx = (int)shape;
	if (idx < 0 || idx >= (int)SHAPE_COUNT || tbl[idx] == NULL)
		return (pos_fallback(fdf, p, out));
	tbl[idx](fdf, p, out);
}

// Add overloaded version for the different call signature
void	get_shape_position_coords(t_shape_type shape, t_app *fdf,
			t_point2 coord, t_fpoint3 *out)
{
	if (!fdf || !out)
		return ;
	get_shape_position(shape, fdf, &coord, out);
}
