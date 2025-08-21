/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:47:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stddef.h>

t_list	*sorted_merge(t_list *head1, t_list *head2)
{
	t_list	dummy;
	t_list	*curr;

	curr = &dummy;
	while (head1 != NULL && head2 != NULL)
	{
		if (*(int *)(head1->content) <= *(int *)(head2->content))
		{
			curr->next = head1;
			head1 = head1->next;
		}
		else
		{
			curr->next = head2;
			head2 = head2->next;
		}
		curr = curr->next;
	}
	if (head1 == NULL)
		curr->next = head2;
	else
		curr->next = head1;
	return (dummy.next);
}
