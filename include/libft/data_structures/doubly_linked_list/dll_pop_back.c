/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_pop_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:41:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doubly_list.h"

void	*ft_dll_pop_back(t_doubly_list *list)
{
	t_dll_node	*temp;
	void		*data;

	if (!list || ft_dll_is_empty(list))
		return (NULL);
	temp = list->tail;
	data = temp->data;
	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;
	else
		list->head = NULL;
	free(temp);
	list->size--;
	return (data);
}
