/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_dance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:30:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 12:41:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include <stdint.h>
#include <stdlib.h>
#include "fdf.h"
// Start/stop dancing system
void	dance_system_toggle(void)
{
	t_dance_system	*d;

	d = gdance(NULL);
	d->active = !d->active;
	if (d->active)
	{
		d->current_move = DANCE_SPIN;
		d->time_accumulator = 0.0f;
		d->move_frame = 0;
		d->hold_frame = 0;
		d->transitioning = false;
		ft_printf("🎉🕺 ULTIMATE DANCE MODE ACTIVATED!"
			"GET READY FOR THE SHOW! 🕺🎉\n");
		ft_printf("💃 Your 3D model is about to PARTY HARD! 💃\n");
	}
	else
		ft_printf("🛑 Dance mode deactivated - party's over! 🛑\n");
}

// Check if dancing is active
bool	dance_system_is_active(void)
{
	return (gdance(NULL)->active);
}

// Set dance rhythm speed
void	dance_system_set_rhythm(float multiplier)
{
	t_dance_system	*d;

	d = gdance(NULL);
	d->rhythm_multiplier = fmaxf(0.1f, fminf(5.0f, multiplier));
}
