/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:36:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 00:36:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_z_perspective_control(void)
{
	t_z_perspective	ctrl;

	ctrl = gzperspective(NULL);
	if (ctrl.original_z_values)
	{
		free(ctrl.original_z_values);
		ctrl.original_z_values = NULL;
	}
	ctrl.initialized = false;
	ctrl.scale_factor = 1.0f;
	gzperspective(&ctrl);
}
