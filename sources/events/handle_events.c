/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlde_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:11:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 00:30:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	toggle_effects(t_app *fdf, int keycode, void *data);

int	modifier_index(unsigned int mods)
{
	int	index;

	index = 0;
	if (mods & ShiftMask)
		index |= 1;
	if (mods & ControlMask)
		index |= 2;
	if (mods & Mod1Mask)
		index |= 4;
	return (index);
}

void	setup_movement_bindings(void)
{
	register_event_binding(W, 0, move_up);
	register_event_binding(A, 0, move_left);
	register_event_binding(S, 0, move_down);
	register_event_binding(D, 0, move_right);
	register_event_binding(ARROW_UP, 0, rotate_up_handler);
	register_event_binding(ARROW_DOWN, 0, rotate_down_handler);
	register_event_binding(ARROW_LEFT, 0, rotate_left_handler);
	register_event_binding(ARROW_RIGHT, 0, rotate_right_handler);
}

void	setup_control_bindings(void)
{
	register_event_binding(P, 0, projection_fly);
	register_event_binding(I, 0, project_iso);
	register_event_binding(T, 0, ch_shape);
	register_event_binding(R, 0, reset_state);
	register_event_binding(65307, 0, exit_prog);
	register_event_binding(XK_plus, 0, zoom_in);
	register_event_binding(XK_minus, 0, zoom_out);
	register_event_binding(XK_KP_Add, 0, zoom_in);
	register_event_binding(XK_KP_Subtract, 0, zoom_out);
	register_event_binding(SPACE_BAR, 0, auto_rotate);
	register_event_binding(ARROW_UP, ControlMask, z_perspective_ctrl);
	register_event_binding(ARROW_DOWN, ControlMask, z_perspective_ctrl);
	register_event_binding(65362, ControlMask, z_perspective_ctrl);
	register_event_binding(65364, ControlMask, z_perspective_ctrl);
	register_event_binding(XK_equal, 0, z_perspective_ctrl);
	register_event_binding(XK_minus, 0, z_perspective_ctrl);
}

void	setup_palette_bindings(void)
{
	register_event_binding(ONE, 0, palette_1_handler);
	register_event_binding(TWO, 0, palette_2_handler);
	register_event_binding(THREE, 0, palette_3_handler);
	register_event_binding(FOUR, 0, palette_4_handler);
	register_event_binding(FIVE, 0, palette_5_handler);
	register_event_binding(SIX, 0, palette_6_handler);
	register_event_binding(SEVEN, 0, palette_7_handler);
	register_event_binding(EIGHT, 0, palette_8_handler);
	register_event_binding(NINE, 0, palette_9_handler);
}

void	setup_feature_toggle_bindings(void)
{
	register_event_binding(H, 0, toggle_effects);
	register_event_binding(G, 0, ch_particules);
	register_event_binding(Z_KEY, 0, dance_toggle_handler);
	register_event_binding(B, 0, dynamic_background_toggle_handler);
	register_event_binding(V, 0, texture_toggle_handler);
	register_event_binding(XK_m, 0, viewmode_toggle_handler);
	register_event_binding(XK_f, 0, camera_toggle_handler);
	register_event_binding(XK_q, 0, cam_down_handler);
	register_event_binding(XK_e, 0, cam_up_handler);
	register_event_binding(XK_F11, 0, viewport_preset_handler);
}
