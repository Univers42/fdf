/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:43:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doubly_list.h"

bool	ft_dll_push_back(t_doubly_list *list, void *data)
{
	t_dll_node	*new_node;

	if (!list)
		return (false);
	new_node = malloc(sizeof(t_dll_node));
	if (!new_node)
		return (false);
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = list->tail;
	if (list->tail)
		list->tail->next = new_node;
	else
		list->head = new_node;
	list->tail = new_node;
	list->size++;
	return (true);
}
