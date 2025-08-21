/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:44:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doubly_list.h"

int	ft_dll_find(t_doubly_list *list, void *data)
{
	t_dll_node	*current;
	int			index;

	if (!list)
		return (-1);
	current = list->head;
	index = 0;
	while (current)
	{
		if (current->data == data)
			return (index);
		current = current->next;
		index++;
	}
	return (-1);
}

bool	ft_dll_contains(t_doubly_list *list, void *data)
{
	return (ft_dll_find(list, data) != -1);
}
