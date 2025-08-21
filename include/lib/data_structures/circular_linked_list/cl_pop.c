/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:27:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

void	*ft_cl_pop_front(t_circular_list *list)
{
	t_cl_node	*first;
	void		*data;

	if (!list || ft_cl_is_empty(list))
		return (NULL);
	first = list->last->next;
	data = first->data;
	if (list->size == 1)
		list->last = NULL;
	else
		list->last->next = first->next;
	free(first);
	list->size--;
	return (data);
}

void	*ft_cl_pop_back(t_circular_list *list)
{
	t_cl_node	*current;
	void		*data;

	if (!list || ft_cl_is_empty(list))
		return (NULL);
	data = list->last->data;
	if (list->size == 1)
	{
		free(list->last);
		list->last = NULL;
	}
	else
	{
		current = list->last->next;
		while (current->next != list->last)
			current = current->next;
		current->next = list->last->next;
		free(list->last);
		list->last = current;
	}
	list->size--;
	return (data);
}
