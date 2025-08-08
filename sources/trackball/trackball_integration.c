/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_integration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:38:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_auto_trackball_rotation(t_app *fdf, float speed)
{
	float	cs;
	float	sn;

	if (!transition_is_active())
		return ;
	cs = cosf(speed);
	sn = sinf(speed);
	rotate_all_points(fdf, cs, sn);
}

void	matrix4_apply_to_point(const float *m, float *x, float *y,
		float *z)
{
	float	v[4];
	float	o[4];
	int		i;
	int		j;

	v[0] = *x;
	v[1] = *y;
	v[2] = *z;
	v[3] = 1.0f;
	i = 0;
	while (i < 4)
	{
		o[i] = 0.0f;
		j = 0;
		while (j < 4)
		{
			o[i] += m[i * 4 + j] * v[j];
			j++;
		}
		i++;
	}
	*x = o[0];
	*y = o[1];
	*z = o[2];
}

void	init_trackball_system(void)
{
	t_trackball_state	*t;

	t = gtrack();
	t->current_quat[0] = 0.0f;
	t->current_quat[1] = 0.0f;
	t->current_quat[2] = 0.0f;
	t->current_quat[3] = 1.0f;
	t->last_quat[0] = 0.0f;
	t->last_quat[1] = 0.0f;
	t->last_quat[2] = 0.0f;
	t->last_quat[3] = 1.0f;
	t->active = false;
	t->initialized = true;
}

void	rotate_all_points(t_app *fdf, float cs, float sn)
{
	t_fpoint2	coord;
	t_fpoint3	p;
	t_fpoint3	r;
	int			idx;

	p.y = 0;
	r.y = 0;
	coord.y = -1;
	while (++coord.y < fdf->height)
	{
		coord.x = -1;
		while (++coord.x < fdf->width)
		{
			idx = coord.y * fdf->width + coord.x;
			p.x = fdf->transformed_points[idx].x;
			p.z = fdf->transformed_points[idx].z;
			r.x = p.x * cs + p.z * sn;
			r.z = -p.x * sn + p.z * cs;
			fdf->transformed_points[idx].x = r.x;
			fdf->transformed_points[idx].z = r.z;
		}
	}
}
