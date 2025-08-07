/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_z2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:42:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 22:46:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_z_perspective_scale(void)
{
	return (gzperspective(NULL).scale_factor);
}

void	set_z_perspective_mode(t_app *fdf, int mode)
{
	t_z_perspective	ctrl;
	float			target_scale;

	ctrl = gzperspective(NULL);
	if (!ctrl.initialized)
		init_z_perspective_control(fdf);
	if (mode < 0 || mode >= 5)
		return ;
	target_scale = get_target_scale(mode);
	ctrl.scale_factor = target_scale;
	update_z_points(fdf, &ctrl);
	gzperspective(&ctrl);
	printf("Z-Perspective mode %d set (scale: %.1f)\n", mode, target_scale);
}
