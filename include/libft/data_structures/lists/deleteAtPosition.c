/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleteAtPosition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:40:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

t_list	*deleteatposition(t_list *head, int pos)
{
	t_list	*curr;
	t_list	*temp;
	int		i;

	if (!head)
		return (NULL);
	if (pos == 1)
	{
		temp = head;
		head = head->next;
		return (free(temp), head);
	}
	curr = head;
	i = 0;
	while (curr && ++i < pos - 1)
		curr = curr->next;
	if (!curr || !curr->next)
		return (head);
	temp = curr->next;
	curr->next = temp->next;
	return (free(temp), head);
}
