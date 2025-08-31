/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_shape1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:10:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:08:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/* forward declarations from postion_shape2.c */
void	pos_dna(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_chips(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_wave(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_heart(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_cone(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_tube(t_app *f, t_point2 *p, t_fpoint3 *o);

/**
 * @brief Computes the original grid position.
 *
 * Sets the output position to the grid coordinates with the original Z value.
 *
 * @param f Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @param o Pointer to the output 3D position.
 */
void	pos_original(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	(void)f;
	o->x = (float)p->x;
	o->y = (float)p->y;
	o->z = orig_z(f, p);
}

/**
 * @brief Computes the torus shape position.
 *
 * Maps the grid point to a position on a torus surface.
 *
 * @param f Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @param o Pointer to the output 3D position.
 */
void	pos_torus(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	major_r;
	float	minor_r;
	float	u;
	float	v;

	major_r = fminf(f->width, f->height) / 3.0f;
	minor_r = major_r / 4.0f;
	u = (2.0f * M_PI * (float)p->x) / (float)(f->width - 1);
	v = (2.0f * M_PI * (float)p->y) / (float)(f->height - 1);
	o->x = (major_r + minor_r * cosf(v)) * cosf(u);
	o->y = (major_r + minor_r * cosf(v)) * sinf(u);
	o->z = minor_r * sinf(v) + orig_z(f, p) * 0.05f;
}

/**
 * @brief Computes the sphere shape position.
 *
 * Maps the grid point to a position on a sphere surface.
 *
 * @param f Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @param o Pointer to the output 3D position.
 */
void	pos_sphere(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	r;
	float	theta;
	float	phi;

	r = fminf(f->width, f->height) / 3.0f;
	theta = (2.0f * M_PI * (float)p->x) / (float)(f->width - 1);
	phi = (M_PI * (float)p->y) / (float)(f->height - 1);
	o->x = r * sinf(phi) * cosf(theta);
	o->y = r * sinf(phi) * sinf(theta);
	o->z = r * cosf(phi) + orig_z(f, p) * 0.05f;
}

/**
 * @brief Computes the cube shape position.
 *
 * Maps the grid point to a position approximating a cube surface.
 *
 * @param f Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @param o Pointer to the output 3D position.
 */
void	pos_cube(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	cube_sz;
	float	nx;
	float	ny;
	float	dist;

	cube_sz = fminf(f->width, f->height) / 3.0f;
	nx = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	o->x = nx * cube_sz / 2.0f;
	o->y = ny * cube_sz / 2.0f;
	if (fabsf(nx) <= 0.8f && fabsf(ny) <= 0.8f)
	{
		dist = sqrtf(nx * nx + ny * ny);
		o->z = cube_sz / 2.0f * (1.0f - dist * 0.3f) + orig_z(f, p) * 0.1f;
	}
	else
		o->z = orig_z(f, p) * 0.1f;
}
