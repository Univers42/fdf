/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issorted.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:50:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:51:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int	issorted(t_list *head)
{
	t_list	*current;
	int		non_decreasing;
	int		non_increasing;

	if (!head || !head->next)
		return (1);
	non_decreasing = 1;
	non_increasing = 1;
	current = head;
	while (current->next)
	{
		if (*(int *)(current->content) > *(int *)(current->next->content))
			non_decreasing = 0;
		if (*(int *)(current->content) < *(int *)(current->next->content))
			non_increasing = 0;
		if (!non_decreasing && !non_increasing)
			return (0);
		current = current->next;
	}
	return (1);
}
