/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_destroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:27:51 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:31:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"
#include <stdlib.h>

void	input_destroy(struct s_input_event *self)
{
	if (self == NULL)
		return ;
	self->event_count = 0;
	self->mlx_ptr = NULL;
	self->win_ptr = NULL;
	free(self);
}

void	destroy_method(t_input_event *self)
{
	if (self)
		free(self);
}
