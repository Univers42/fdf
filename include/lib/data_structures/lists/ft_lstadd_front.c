/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:37:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * Adds a new node to the front of a linked list.
 * 
 * @param lst A double pointer to the first node of the list.
 *            If the list is empty, the new node becomes the first node.
 * @param new A pointer to the new node to add to the front of the list.
 * 
 * @return Nothing.
 * 
 * @note 
 * The function does not handle memory 
 * allocation for the new node;
 * it assumes the `new` node is already 
 * allocated and properly initialized.
 */

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}

//int main(void)
//{
//    // Create the first node
//    t_list *new_node = ft_lstnew(ft_strdup("Hello world!"));
//    if (!new_node)
//        return 1;
//
//    // Create the second node
//    t_list *another_node = ft_lstnew(ft_strdup("My name is Carter!"));
//    if (!another_node)
//    {
//        free(new_node->content);
//        free(new_node);
//        return 1;
//    }
//
//    // Create the node to add at the front
//    t_list *node = ft_lstnew(ft_strdup("Before"));
//    if (!node)
//    {
//        free(new_node->content);
//        free(new_node);
//        free(another_node->content);
//        free(another_node);
//        return 1;
//    }
//
//    // Link the list
//    new_node->next = another_node;
//
//    // Add the new node at the front
//    ft_lstadd_front(&new_node, node);
//
//    // Print the list
//    t_list *curr = new_node;
//    while (curr)
//    {
//       	ft_printf("%s\n", (char *)curr->content);
//        curr = curr->next;
//    }
//
//    // Free the list
//    curr = new_node;
//    while (curr)
//    {
//        t_list *temp = curr->next;
//        free(curr->content);
//        free(curr);
//        curr = temp;
//    }
//
//    return 0;
//}
//void	del(void *content)
//{
//	free(content);	
//}
////int main(void)
////{
////	t_list *head = ft_lstnew(ft_strdup("BASE"));
////	if(!head)
////		return 1;
////	for(int i = 0; i < 10; i++)
////	{
////		t_list *new_node = ft_lstnew(ft_strdup("grooots"));
////		if(!new_node)
////		{
////			ft_lstclear(&head, &del);
////			return 2;
////		}
////		ft_lstadd_front(&head, new_node);
////	}
////	ft_lstadd_back(&head, ft_lstnew(ft_strdup("TAIL")));
////	ft_printf("Size Before ft_lstclear(): %d\n", ft_lstsize(head));
////	ft_lstclear(&head, &del);
////	ft_printf("Size after ft_lstclear(): %d\n");
////}