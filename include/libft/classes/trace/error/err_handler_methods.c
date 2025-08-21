/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler_methods.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 16:36:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err_handler.h"
#include <stdlib.h>

static void	handler_set_error(
	t_handler *self, int code, t_err_ctx *ctx)
{
	if (self)
	{
		self->last_error = code;
		if (ctx)
		{
			self->file = ctx->file;
			self->func = ctx->func;
			self->line = ctx->line;
		}
	}
}

static const char	*handler_get_message(
	t_handler *self, int code)
{
	t_interface	*reg;
	const char	*msg;

	(void) self;
	reg = err_default_registry();
	msg = reg->get_message(reg, code);
	if (msg)
		return (msg);
	else
		return ("Unknown error");
}

t_handler	*err_handler_create(void)
{
	t_handler	*handler;

	handler = calloc(1, sizeof(t_handler));
	if (!handler)
		return (NULL);
	handler->set_error = handler_set_error;
	handler->get_message = handler_get_message;
	return (handler);
}

void	err_handler_destroy(t_handler *handler)
{
	free(handler);
}
