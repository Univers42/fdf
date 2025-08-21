/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:24:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

void	*ft_cl_front(t_circular_list *list)
{
	if (!list || ft_cl_is_empty(list))
		return (NULL);
	return (list->last->next->data);
}

void	*ft_cl_back(t_circular_list *list)
{
	if (!list || ft_cl_is_empty(list))
		return (NULL);
	return (list->last->data);
}

static t_cl_node	*get_node_at_index(t_circular_list *list, size_t index)
{
	t_cl_node	*current;
	size_t		i;

	if (!list || index >= list->size)
		return (NULL);
	current = list->last->next;
	i = -1;
	while (++i < index)
		current = current->next;
	return (current);
}

void	*ft_cl_get(t_circular_list *list, size_t index)
{
	t_cl_node	*node;

	node = get_node_at_index(list, index);
	if (!node)
		return (NULL);
	return (node->data);
}

bool	ft_cl_set(t_circular_list *list, size_t index, void *data)
{
	t_cl_node	*node;

	node = get_node_at_index(list, index);
	if (!node)
		return (false);
	node->data = data;
	return (true);
}
