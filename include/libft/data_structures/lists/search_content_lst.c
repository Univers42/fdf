/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_content_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:48:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stddef.h>

int	search_content_lst(t_list *head, int x)
{
	t_list	*curr;

	curr = head;
	while (curr != NULL)
	{
		if (*(int *)(curr->content) == x)
			return (1);
		curr = curr->next;
	}
	return (0);
}
