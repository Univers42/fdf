/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postion_shape2.c                                   :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static inline float	orig_z(t_app *f, t_point2 *p)
{
	t_transition_state	*st;
	int					i;

	st = gtransition(NULL);
	if (!st || !st->original_positions)
		return (0.0f);
	i = p->y * f->width + p->x;
	if (i < 0 || i >= f->width * f->height)
		return (0.0f);
	return (st->original_positions[i * 3 + 2]);
}

void	pos_dna(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	r;
	float	ny;
	float	ang;
	float	phase;

	r = fminf(f->width, f->height) / 6.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	ang = ny * 4.0f * M_PI;
	phase = ((p->x % 2) == 0) ? 0.0f : M_PI;
	o->x = r * cosf(ang + phase);
	o->y = ny * f->height * 0.4f;
	o->z = r * sinf(ang + phase) + orig_z(f, p) * 0.02f;
}

void	pos_chips(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	s;
	float	nx;
	float	ny;

	s = fminf(f->width, f->height) / 3.0f;
	nx = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	o->x = nx * s;
	o->y = ny * s;
	o->z = 0.3f * (nx * nx - ny * ny) * s + orig_z(f, p) * 0.1f;
}

void	pos_wave(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	a;
	float	b;
	float	nx;
	float	ny;

	a = fminf(f->width, f->height) / 6.0f;
	b = fminf(f->width, f->height) / 3.0f;
	nx = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	o->x = nx * b;
	o->y = ny * b;
	o->z = a * sinf(nx * 3.0f * M_PI) * cosf(ny * 3.0f * M_PI)
		+ orig_z(f, p) * 0.1f;
}

void	pos_heart(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	s;
	float	nx;
	float	ny;
	float	dist1;
	float	dist2;
	float	point_factor;

	s = fminf(f->width, f->height) / 4.0f;
	nx = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	ny = -((2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f);
	o->x = nx * s;
	o->y = ny * s;
	if (ny > 0.0f)
	{
		dist1 = sqrtf((nx + 0.5f) * (nx + 0.5f) + (ny - 0.3f) * (ny - 0.3f));
		dist2 = sqrtf((nx - 0.5f) * (nx - 0.5f) + (ny - 0.3f) * (ny - 0.3f));
		o->z = (dist1 < 0.6f || dist2 < 0.6f) ? s * 0.3f : 0.0f;
	}
	else
	{
		point_factor = 1.0f + ny;
		if (point_factor > 0.0f && fabsf(nx) < point_factor * 0.8f)
			o->z = s * 0.2f * point_factor;
		else
			o->z = 0.0f;
	}
	o->z += orig_z(f, p) * 0.02f;
}

void	pos_cone(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	max_r;
	float	ang;
	float	h;
	float	hl;
	float	r;

	max_r = fminf(f->width, f->height) / 4.0f;
	ang = ((float)p->x / (float)f->width) * 2.0f * M_PI;
	h = (float)p->y - (float)f->height / 2.0f;
	hl = (float)f->height * 0.5f;
	if (fabsf(h) < hl)
	{
		r = max_r * (1.0f - fabsf(h) / hl);
		o->x = r * cosf(ang);
		o->y = h;
		o->z = r * sinf(ang);
	}
	else
	{
		o->x = 0.0f;
		o->y = h;
		o->z = 0.0f;
	}
}

void	pos_tube(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	br;
	float	hl;
	float	ang;
	float	r;
	float	h;

	br = fminf(f->width, f->height) / 4.0f;
	hl = (float)f->height * 0.5f;
	ang = ((float)p->x / (float)f->width) * 2.0f * M_PI;
	r = br + orig_z(f, p) * 0.3f;
	h = (float)p->y - (float)f->height / 2.0f;
	if (fabsf(h) >= hl * 0.95f)
	{
		float	cx;
		float	cy;
		float	dx;
		float	dy;
		float	gr;
		float	mr;
		float	cr;

		cx = (float)f->width / 2.0f;
		cy = (float)f->height / 2.0f;
		dx = (float)p->x - cx;
		dy = (p->y < cy) ? (float)p->y - 0.0f : (float)p->y - (float)(f->height - 1);
		gr = sqrtf(dx * dx + dy * dy);
		mr = (float)f->width / 2.0f;
		if (gr <= mr)
		{
			cr = (gr / mr) * r;
			o->x = cr * cosf(ang);
			o->y = h;
			o->z = cr * sinf(ang);
			return ;
		}
		o->x = 0.0f;
		o->y = h;
		o->z = 0.0f;
		return ;
	}
	o->x = r * cosf(ang);
	o->y = h;
	o->z = r * sinf(ang);
}
