/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:29:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

bool	ft_cl_push_front(t_circular_list *list, void *data)
{
	t_cl_node	*new_node;

	if (!list)
		return (false);
	new_node = malloc(sizeof(t_cl_node));
	if (!new_node)
		return (false);
	new_node->data = data;
	if (ft_cl_is_empty(list))
	{
		new_node->next = new_node;
		list->last = new_node;
	}
	else
	{
		new_node->next = list->last->next;
		list->last->next = new_node;
	}
	list->size++;
	return (true);
}

bool	ft_cl_push_back(t_circular_list *list, void *data)
{
	t_cl_node	*new_node;

	if (!list)
		return (false);
	new_node = malloc(sizeof(t_cl_node));
	if (!new_node)
		return (false);
	new_node->data = data;
	if (ft_cl_is_empty(list))
	{
		new_node->next = new_node;
		list->last = new_node;
	}
	else
	{
		new_node->next = list->last->next;
		list->last->next = new_node;
		list->last = new_node;
	}
	list->size++;
	return (true);
}
