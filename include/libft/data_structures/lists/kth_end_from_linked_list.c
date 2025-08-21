/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kth_end_from_linked_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:50:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stddef.h>

int	kth_end_from_linked_list(t_list *head, int k)
{
	t_list	*fast;
	t_list	*slow;
	int		i;

	if (head == NULL)
		return (-1);
	fast = head;
	slow = head;
	i = 1;
	while (i < k)
	{
		if (fast->next == NULL)
			return (-1);
		fast = fast->next;
		i++;
	}
	while (fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next;
	}
	return (*(int *)(slow->content));
}
