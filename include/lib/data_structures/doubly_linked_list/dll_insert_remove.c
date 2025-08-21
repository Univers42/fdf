/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_insert_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:40:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doubly_list.h"

bool	ft_dll_insert(t_doubly_list *list, size_t index, void *data)
{
	t_dll_node	*new_node;
	t_dll_node	*current;
	size_t		i;

	if (!list || index > list->size)
		return (false);
	if (index == 0)
		return (ft_dll_push_front(list, data));
	if (index == list->size)
		return (ft_dll_push_back(list, data));
	new_node = malloc(sizeof(t_dll_node));
	if (!new_node)
		return (false);
	current = list->head;
	i = -1;
	while (++i < index)
		current = current->next;
	new_node->data = data;
	new_node->next = current;
	new_node->prev = current->prev;
	current->prev->next = new_node;
	current->prev = new_node;
	list->size++;
	return (true);
}

void	*ft_dll_remove(t_doubly_list *list, size_t index)
{
	t_dll_node	*current;
	void		*data;
	size_t		i;

	if (!list || index >= list->size)
		return (NULL);
	if (index == 0)
		return (ft_dll_pop_front(list));
	if (index == list->size - 1)
		return (ft_dll_pop_back(list));
	current = list->head;
	i = -1;
	while (++i < index)
		current = current->next;
	data = current->data;
	current->prev->next = current->next;
	current->next->prev = current->prev;
	free(current);
	list->size--;
	return (data);
}

bool	ft_dll_remove_data(t_doubly_list *list, void *data)
{
	int	index;

	index = ft_dll_find(list, data);
	if (index == -1)
		return (false);
	ft_dll_remove(list, index);
	return (true);
}
