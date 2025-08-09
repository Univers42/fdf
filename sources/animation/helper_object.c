/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:41:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:17:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Toggle auto-sequence mode
void	dance_system_toggle_auto_sequence(void)
{
	t_dance_system	*d;

	d = gdance(NULL);
	d->auto_sequence = !d->auto_sequence;
}

void	(**dance_move_fn(void))(t_app *fdf)
{
	static void	(*table[DANCE_MOVE_COUNT])(t_app *fdf) = {
		NULL,
		apply_dance_spin,
		apply_dance_bounce,
		apply_dance_wave_motion,
		apply_dance_twist,
		apply_dance_expand_contract,
		apply_dance_figure_eight,
		apply_dance_wobble
	};

	return (table);
}

bool	object_effects_is_active(void)
{
	return (gobjfx(NULL)->current_effect != OBJ_EFFECT_NONE);
}

void	set_object_effect_intensity(float intensity)
{
	t_object_effects_system	*oe;

	oe = gobjfx(NULL);
	oe->intensity = fmaxf(0.1f, fminf(2.0f, intensity));
}
