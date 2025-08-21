/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:31:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 16:03:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"
#include "theme.h"

void	color_snapshot_restore(t_app *fdf);

static void	reset_transformations(t_app *fdf)
{
	t_projection_ctl	*projection;

	reset_trackball_rotation();
	make_trans_stack(&fdf->trans_stack);
	trans_stack_origin(&fdf->trans_stack,
		-((float)fdf->width / 2), -((float)fdf->height / 2),
		-(float)(fdf->min_z + fdf->max_z) / 2.0f);
	trans_stack_isometric(&fdf->trans_stack);
	projection = &fdf->trans_stack.projection;
	make_projection_ctl(projection, (float)fdf->width, (float)fdf->height,
		(float)(fdf->max_z - fdf->min_z));
	trans_stack_translate(&fdf->trans_stack, 0, 0,
		-projection->box[2] / 2.0f);
	projection_reset_params(projection);
	fdf->trans_stack.dirty[M_PROJECTION] = true;
	trans_stack_update(&fdf->trans_stack);
	center_model(&fdf->trans_stack, (float)fdf->width,
		(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
}

void	reset_state(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	transition_cleanup(fdf);
	particles_cleanup();
	dance_system_cleanup();
	object_effects_cleanup(fdf);
	texture_system_cleanup();
	dynamic_background_cleanup();
	fdf->auto_rotate = false;
	fdf->palette_state.current = 0;
	color_snapshot_restore(fdf);
	reset_transformations(fdf);
	reset_z_perspective(fdf);
	ft_printf("All systems reset to default state\n");
}
