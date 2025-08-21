/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:58:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 10:12:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * Returns the last node in the linked list.
 * 
 * @param lst A pointer to the first node of the list.
 * @return The last node of the list. If the list is empty, returns NULL.
 * 
 * @note 
 * In a singly linked list, there is no direct access to the last node,
 * so this function iterates through the entire list (O(n) time complexity
 * until it reaches the node whose `next` pointer is NULL.
 * This is necessary as there's no way to directly access the last node       
 * without traversing the list.
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}
