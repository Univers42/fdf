/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:28:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:37:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	z_perspective_ctrl(t_app *fdf, int keycode, void *data)
{
	(void)data;
	printf("Z-perspective control triggered with keycode: %d\n", keycode);
	if (keycode == XK_Up || keycode == XK_equal || keycode == XK_plus)
	{
		increase_z_perspective(fdf);
		printf("Z-perspective increased\n");
	}
	else if (keycode == XK_Down || keycode == XK_underscore
		|| keycode == XK_minus)
	{
		reduce_z_perspective(fdf);
		printf("Z-perspective reduced\n");
	}
	else
		printf("Unknown z-perspective control keycode: %d\n", keycode);
}

void	ch_shape(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	(void)fdf;
	transition_start_torus(false);
	printf("Shape transformation activated\n");
}

void	ch_particules(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	(void)fdf;
	transition_start_particles(false);
	printf("Particle system activated\n");
}

void	ch_effect(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	(void)fdf;
	transition_start_object_effects(false);
	printf("Object effects system activated\n");
}
