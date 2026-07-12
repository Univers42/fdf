/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_z1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:39:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 20:22:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	copy_original_z_values(t_app *fdf, t_z_perspective *ctrl)
{
	int	i;

	if (ctrl->original_z_values)
		free(ctrl->original_z_values);
	ctrl->original_z_values = malloc(sizeof(float) * ctrl->total_points);
	if (!ctrl->original_z_values)
		return ;
	i = 0;
	while (i < ctrl->total_points)
	{
		ctrl->original_z_values[i] = fdf->points[i];
		i++;
	}
}

void	init_z_perspective_control(t_app *fdf)
{
	t_z_perspective	ctrl;

	ctrl = gzperspective(NULL);
	if (ctrl.initialized && ctrl.original_z_values)
		return ;
	ctrl.total_points = fdf->width * fdf->height;
	ctrl.original_max_z = fdf->max_z;
	ctrl.original_min_z = fdf->min_z;
	ctrl.scale_factor = 1.0f;
	copy_original_z_values(fdf, &ctrl);
	if (!ctrl.original_z_values)
		return ;
	ctrl.initialized = true;
	gzperspective(&ctrl);
}

void	reduce_z_perspective(t_app *fdf)
{
	update_z_perspective(fdf, -Z_SCALE_STEP);
}

void	increase_z_perspective(t_app *fdf)
{
	update_z_perspective(fdf, Z_SCALE_STEP);
}

void	reset_z_perspective(t_app *fdf)
{
	t_z_perspective	ctrl;
	int				i;

	ctrl = gzperspective(NULL);
	if (!ctrl.initialized || !ctrl.original_z_values)
		return ;
	ctrl.scale_factor = 1.0f;
	i = 0;
	while (i < ctrl.total_points)
	{
		fdf->points[i] = ctrl.original_z_values[i];
		i++;
	}
	fdf->max_z = ctrl.original_max_z;
	fdf->min_z = ctrl.original_min_z;
	gzperspective(&ctrl);
	ft_printf("Z-Perspective reset (original range: %d to %d)\n",
		fdf->min_z, fdf->max_z);
}
