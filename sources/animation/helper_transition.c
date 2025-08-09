/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition.c                                :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* table is defined in position_shape1.c */
extern t_shape_pos_fn	*shape_pos_tbl(void);

static void	pos_fallback(t_app *fdf, t_point2 *p, t_fpoint3 *o)
{
	(void)fdf;
	if (!p || !o)
		return;
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
void	get_shape_position_coords(t_shape_type shape, t_app *fdf, int x, int y,
	float *sx, float *sy, float *sz)
{
	t_point2	p;
	t_fpoint3	out;

	if (!fdf || !sx || !sy || !sz)
		return;
	p.x = x;
	p.y = y;
	get_shape_position(shape, fdf, &p, &out);
	*sx = out.x;
	*sy = out.y;
	*sz = out.z;
}