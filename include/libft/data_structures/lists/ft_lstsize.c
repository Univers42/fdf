/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:50 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 10:11:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * Returns the number of nodes in the linked list.
 * 
 * @param lst A pointer to the first node of the list.
 * @return The number of nodes in the list.
 * 
 * @note This function iterates through the entire list, counting each node until
 *       it reaches the end (when the next pointer is NULL).
 */
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		++count;
		lst = lst->next;
	}
	return (count);
}
