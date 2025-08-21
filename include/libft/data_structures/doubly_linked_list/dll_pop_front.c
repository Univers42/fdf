/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_pop_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:42:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doubly_list.h"

void	*ft_dll_pop_front(t_doubly_list *list)
{
	t_dll_node	*temp;
	void		*data;

	if (!list || ft_dll_is_empty(list))
		return (NULL);
	temp = list->head;
	data = temp->data;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;
	else
		list->tail = NULL;
	free(temp);
	list->size--;
	return (data);
}
