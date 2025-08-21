/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:46:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doubly_list.h"

size_t	ft_dll_size(t_doubly_list *list)
{
	if (!list)
		return (0);
	return (list->size);
}

bool	ft_dll_is_empty(t_doubly_list *list)
{
	if (!list || list->size == 0)
		return (true);
	return (false);
}

void	ft_dll_clear(t_doubly_list *list)
{
	t_dll_node	*current;
	t_dll_node	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

void	ft_dll_reverse(t_doubly_list *list)
{
	t_dll_node	*current;
	t_dll_node	*temp;

	if (!list || list->size <= 1)
		return ;
	current = list->head;
	while (current)
	{
		temp = current->next;
		current->next = current->prev;
		current->prev = temp;
		current = temp;
	}
	temp = list->head;
	list->head = list->tail;
	list->tail = temp;
}
