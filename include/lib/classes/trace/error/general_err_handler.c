/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_err_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/28 17:14:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err_handler.h"
#include <stdlib.h>
#include <string.h>

static int	registry_add_message(
	t_interface *self, int code, const char *message)
{
	struct s_registry_impl	*impl;
	struct s_err_entry		*entry;

	if (!self || !message)
		return (-1);
	impl = (struct s_registry_impl *)self->impl;
	entry = malloc(sizeof(struct s_err_entry));
	if (!entry)
		return (-1);
	entry->code = code;
	entry->message = strdup(message);
	entry->next = impl->head;
	impl->head = entry;
	return (0);
}

static const char	*registry_get_message(
	t_interface *self, int code)
{
	struct s_registry_impl	*impl;
	struct s_err_entry		*cur;

	if (!self)
		return (NULL);
	impl = (struct s_registry_impl *)self->impl;
	cur = impl->head;
	while (cur)
	{
		if (cur->code == code)
			return (cur->message);
		cur = cur->next;
	}
	return (NULL);
}

static void	registry_destroy(
	t_interface *self)
{
	struct s_registry_impl	*impl;
	struct s_err_entry		*cur;
	struct s_err_entry		*next;

	if (!self)
		return ;
	impl = (struct s_registry_impl *)self->impl;
	cur = impl->head;
	while (cur)
	{
		next = cur->next;
		free((void *)cur->message);
		free(cur);
		cur = next;
	}
	free(impl);
	free(self);
}

t_interface	*err_registry_create(void)
{
	t_interface				*reg;
	struct s_registry_impl	*impl;

	reg = malloc(sizeof(t_interface));
	if (!reg)
		return (NULL);
	impl = malloc(sizeof(struct s_registry_impl));
	if (!impl)
	{
		free(reg);
		return (NULL);
	}
	impl->head = NULL;
	reg->add_message = registry_add_message;
	reg->get_message = registry_get_message;
	reg->destroy = registry_destroy;
	reg->impl = impl;
	return (reg);
}

t_interface	*err_default_registry(void)
{
	static t_interface	*singleton = NULL;

	if (!singleton)
	{
		singleton = err_registry_create();
		singleton->add_message(singleton, 0, "No error");
		singleton->add_message(singleton, 1, "Allocation failed");
		singleton->add_message(singleton, 2, "Invalid input");
	}
	return (singleton);
}
