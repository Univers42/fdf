/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:42:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 10:12:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * Iterates through the entire list, 
 * applying the function `f` to each node's content.
 * 
 * @param lst A pointer to the first node of the list.
 * @param f A function pointer that will be applied to each node's content.
 * 
 * @return Nothing.
 * 
 * @note 
 * This function does not modify the list itself. 
 * It only applies the function `f`
 * to each node's content without 
 * altering the structure of the list.
 */

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
