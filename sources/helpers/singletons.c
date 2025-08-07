/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:40:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 22:40:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_z_perspective	gzperspective(t_z_perspective *set)
{
	static t_z_perspective	g_z_control = {
		.scale_factor = 1.0f,
		.original_max_z = 0.0f,
		.original_min_z = 0.0f,
		.initialized = false,
		.original_z_values = NULL,
		.total_points = 0
	};

	if (set)
		g_z_control = *set;
	return (g_z_control);
}

