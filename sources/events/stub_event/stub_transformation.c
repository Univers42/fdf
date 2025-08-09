/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:28:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 02:12:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	z_perspective_ctrl(t_app *fdf, int keycode, void *data)
{
	(void)data;
	ft_printf("Z-perspective control triggered with keycode: %d\n", keycode);
	if (keycode == XK_Up || keycode == XK_equal || keycode == XK_plus)
	{
		increase_z_perspective(fdf);
		ft_printf("Z-perspective increased\n");
	}
	else if (keycode == XK_Down || keycode == XK_underscore
		|| keycode == XK_minus)
	{
		reduce_z_perspective(fdf);
		ft_printf("Z-perspective reduced\n");
	}
	else
		ft_printf("Unknown z-perspective control keycode: %d\n", keycode);
}

void	ch_shape(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	// Start next shape in the cycle using the per-app transition state
	transition_start_shape_cycle(fdf);
}

void	ch_particules(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	(void)fdf;
	transition_start_particles(false);
	ft_printf("Particle system activated\n");
}

void	ch_effect(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	(void)fdf;
	transition_start_object_effects(false);
	ft_printf("Object effects system activated\n");
}
