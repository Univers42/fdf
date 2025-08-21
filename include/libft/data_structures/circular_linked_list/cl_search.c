/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:30:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

int	ft_cl_find(t_circular_list *list, void *data)
{
	t_cl_node	*current;
	int			index;
	size_t		i;

	if (!list || ft_cl_is_empty(list))
		return (-1);
	current = list->last->next;
	index = 0;
	i = 0;
	while (i < list->size)
	{
		if (current->data == data)
			return (index);
		current = current->next;
		index++;
		i++;
	}
	return (-1);
}

bool	ft_cl_contains(t_circular_list *list, void *data)
{
	return (ft_cl_find(list, data) != -1);
}
