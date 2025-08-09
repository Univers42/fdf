/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_particule3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:04:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:05:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ps_transition_step(t_particle_transition *ps)
{
	if (!ps->active)
		return ;
	ps->frame++;
	if (ps->frame >= ps->max_frames)
	{
		ps->active = false;
		ps->frame = 0;
		ps->current_type = ps->target_type;
	}
}

void	ps_update_all(t_particle_transition *ps)
{
	int	i;

	i = 0;
	while (i < MAX_PARTICLES)
	{
		update_particle(&ps->particles[i], ps->current_type);
		i++;
	}
}
