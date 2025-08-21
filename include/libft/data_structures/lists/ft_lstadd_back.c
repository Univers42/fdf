/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:11:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * Adds a new node to the end of a linked list.
 * 
 * @param lst A double pointer to the first node of the list.
 *            If the list is empty, new node becomes first node.
 * @param new
 * A pointer to the new node to add to the end of the list.
 * 
 * @return Nothing.
 * 
 * @note
 * The function does not handle 
 * memory allocation for the new node;
 * it assumes the `new` node is 
 * already allocated and properly initialized.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		node = ft_lstlast(*lst);
		node->next = new;
	}
}
//int main(void)
//{
//	t_list *head = ft_lstnew(ft_strdup("BASE"));
//	if(!head)
//		return 1;
//	for(int i = 0; i < 10; i++)
//	{
//		t_list *new_node = ft_lstnew(ft_strdup("grooots"));
//		if(!new_node)
//		{
//			ft_lstclear(&head, &del);
//			return 2;
//		}
//		ft_lstadd_front(&head, new_node);
//	}
//	ft_lstadd_back(&head, ft_lstnew(ft_strdup("TAIL")));
//	ft_printf("Size Before ft_lstclear(): %d\n", ft_lstsize(head));
//	ft_lstclear(&head, &del);
//	ft_printf("Size after ft_lstclear(): %d\n");
//}
//