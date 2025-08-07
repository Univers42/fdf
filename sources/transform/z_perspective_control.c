/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_perspective_control.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 22:45:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static float	apply_positive_convergence(float scaled_z)
{
	float	excess;
	float	converged_excess;

	if (scaled_z > CONVERGENCE_THRESHOLD)
	{
		excess = scaled_z - CONVERGENCE_THRESHOLD;
		converged_excess = excess * CONVERGENCE_FACTOR;
		if (excess > 200.0f)
			converged_excess = 200.0f
				+ logf(1.0f + (excess - 200.0f) / 100.0f) * 50.0f;
		scaled_z = CONVERGENCE_THRESHOLD + converged_excess;
		if (scaled_z > MAX_Z_LIMIT)
			scaled_z = MAX_Z_LIMIT;
	}
	return (scaled_z);
}

static float	apply_convergence(float original_z, float scale_factor)
{
	float	scaled_z;
	float	min_allowed;

	scaled_z = original_z * scale_factor;
	if (original_z >= 0.0f)
	{
		scaled_z = apply_positive_convergence(scaled_z);
		if (scaled_z < MIN_Z_LIMIT)
			scaled_z = MIN_Z_LIMIT;
	}
	else
	{
		min_allowed = gzperspective(NULL).original_min_z * 2.0f;
		if (scaled_z < min_allowed)
			scaled_z = min_allowed;
	}
	return (scaled_z);
}

void	update_z_points(t_app *fdf, t_z_perspective *ctrl)
{
	int		i;
	float	original_z;
	float	new_z;
	float	new_max;
	float	new_min;

	new_max = 0.0f;
	new_min = 0.0f;
	i = 0;
	while (i < ctrl->total_points)
	{
		original_z = ctrl->original_z_values[i];
		new_z = apply_convergence(original_z, ctrl->scale_factor);
		fdf->points[i] = new_z;
		if (i == 0 || new_z > new_max)
			new_max = new_z;
		if (i == 0 || new_z < new_min)
			new_min = new_z;
		i++;
	}
	fdf->max_z = new_max;
	fdf->min_z = new_min;
}

float	get_target_scale(int mode)
{
	const float	scales[] = {0.2f, 0.5f, 1.0f, 1.5f, 2.0f};

	if (mode >= 0 && mode < 5)
		return (scales[mode]);
	return (1.0f);
}

void	update_z_perspective(t_app *fdf, float scale_change)
{
	t_z_perspective	ctrl;

	ctrl = gzperspective(NULL);
	if (!ctrl.initialized)
		init_z_perspective_control(fdf);
	if (!ctrl.original_z_values)
		return ;
	ctrl.scale_factor += scale_change;
	if (ctrl.scale_factor < 0.1f)
		ctrl.scale_factor = 0.1f;
	if (ctrl.scale_factor > 3.0f)
		ctrl.scale_factor = 3.0f;
	update_z_points(fdf, &ctrl);
	gzperspective(&ctrl);
	printf("Z-Perspective updated (scale: %.1f, range: %d to %d)\n",
		ctrl.scale_factor, fdf->min_z, fdf->max_z);
}
