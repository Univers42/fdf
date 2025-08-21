/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:29:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:32:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"
#include <mlx.h>

void	input_add_event(struct s_input_event *self,
				int keycode, void (*callback)(void *), void *param)
{
	t_event_entry	*ent;

	if (self == NULL || self->event_count >= MAX_EVENTS)
		return ;
	ent = &self->events[self->event_count];
	ent->keycode = keycode;
	ent->callback = callback;
	ent->param = param;
	self->event_count += 1;
}

void	input_prog_hook_events(struct s_input_event *self, void *win)
{
	if (self == NULL)
		return ;
	self->win_ptr = win;
	if (self->mlx_ptr != NULL && self->win_ptr != NULL)
	{
		mlx_hook(self->win_ptr, 2, 1L << 0, handle_keypress, self);
		mlx_hook(self->win_ptr, 17, 0, handle_close, self);
	}
}
