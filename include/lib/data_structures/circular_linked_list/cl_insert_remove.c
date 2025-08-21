/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_insert_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:26:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

bool	ft_cl_insert(t_circular_list *list, size_t index, void *data)
{
	t_cl_node	*new_node;
	t_cl_node	*current;
	size_t		i;

	if (!list || index > list->size)
		return (false);
	if (index == 0)
		return (ft_cl_push_front(list, data));
	if (index == list->size)
		return (ft_cl_push_back(list, data));
	new_node = malloc(sizeof(t_cl_node));
	if (!new_node)
		return (false);
	current = list->last->next;
	i = -1;
	while (++i < index - 1)
		current = current->next;
	new_node->data = data;
	new_node->next = current->next;
	current->next = new_node;
	list->size++;
	return (true);
}

void	*ft_cl_remove(t_circular_list *list, size_t index)
{
	t_cl_node	*current;
	t_cl_node	*to_remove;
	void		*data;
	size_t		i;

	if (!list || index >= list->size)
		return (NULL);
	if (index == 0)
		return (ft_cl_pop_front(list));
	if (index == list->size - 1)
		return (ft_cl_pop_back(list));
	current = list->last->next;
	i = -1;
	while (++i < index - 1)
		current = current->next;
	to_remove = current->next;
	data = to_remove->data;
	current->next = to_remove->next;
	free(to_remove);
	list->size--;
	return (data);
}

bool	ft_cl_remove_data(t_circular_list *list, void *data)
{
	int	index;

	index = ft_cl_find(list, data);
	if (index == -1)
		return (false);
	ft_cl_remove(list, index);
	return (true);
}
