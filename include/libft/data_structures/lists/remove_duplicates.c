/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_duplicates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:49:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

t_list	*remove_duplicates(t_list *head)
{
	t_list	*current;
	t_list	*duplicate;

	current = head;
	while (current != NULL && current->next != NULL)
	{
		if (*(int *)(current->content) == *(int *)(current->next->content))
		{
			duplicate = current->next;
			current->next = current->next->next;
			free(duplicate);
		}
		else
			current = current->next;
	}
	return (head);
}
