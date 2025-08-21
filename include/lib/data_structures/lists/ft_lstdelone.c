/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:33:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 10:13:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * Deletes a single node from the list, using the provided `del` function
 * to free the content of the node and then freeing the node itself.
 * 
 * @param lst A pointer to the node to delete.
 * @param del A function pointer that processes of node's content removing.
 * 
 * @return Nothing.
 * 
 * @note 
 * The function does not handle 
 * the freeing of any other nodes in the list.
 * After calling this function, 
 * the memory for the node and its content is freed.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
