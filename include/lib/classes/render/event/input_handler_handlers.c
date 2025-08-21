/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:29:24 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:29:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

int	handle_keypress(int keycode, void *param)
{
	t_input_event	*e;
	int				i;

	e = (t_input_event *)param;
	if (e == NULL)
		return (0);
	i = 0;
	while (i < e->event_count)
	{
		if (e->events[i].keycode == keycode
			&& e->events[i].callback != NULL)
			e->events[i].callback(e->events[i].param);
		i++;
	}
	return (0);
}

int	handle_close(void *param)
{
	t_input_event	*e;

	e = (t_input_event *)param;
	if (e != NULL && e->destroy != NULL)
		e->destroy(e);
	return (0);
}
