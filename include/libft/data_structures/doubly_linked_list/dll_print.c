/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:42:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doubly_list.h"
#include "../../stdio/ft_stdio.h"

void	ft_dll_print_addresses(t_doubly_list *list)
{
	t_dll_node	*current;

	if (!list)
		return ;
	ft_printf("Doubly Linked List (head -> tail): [");
	current = list->head;
	while (current)
	{
		ft_printf("%p", current->data);
		current = current->next;
		if (current)
			ft_printf(" <-> ");
	}
	ft_printf("]\n");
}

void	ft_dll_print_reverse(t_doubly_list *list)
{
	t_dll_node	*current;

	if (!list)
		return ;
	ft_printf("Doubly Linked List (tail -> head): [");
	current = list->tail;
	while (current)
	{
		ft_printf("%p", current->data);
		current = current->prev;
		if (current)
			ft_printf(" <-> ");
	}
	ft_printf("]\n");
}
