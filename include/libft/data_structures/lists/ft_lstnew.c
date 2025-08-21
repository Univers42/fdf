/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:30:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * --- /!\ MALLOC --> don't forget to verfifye and freed
 * 
 * The purpose of this function is to create and initialize a new node
 * that holds the value provided by the user.
 * 
 * @param content The content to be stored in the new node.
 * @return 
 * A pointer to the newly created node, or NULL if memory allocation fails.
 * 
 * @note 
 * The `next` property of the new node 
 * is initialized to NULL by default, 
 *indicating that it will be the last element 
 in the list unless further connections are made.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
//int main(void)
//{
//	t_list *new_node = ft_lstnew((char *)ft_strdup("Hello, "));
//	if(!new_node)
//		return 1;
//		
//	t_list *another_node = ft_lstnew((char *)ft_strdup("world !"));
//	if(!another_node)
//	{
//		free(new_node->content);
//		free(new_node);
//		return 2;
//	}
//	
//	new_node->next = another_node;
//	t_list *curr = new_node;
//	while(curr != NULL)
//	{
//		ft_printf("%s", (char *)curr->content);
//		curr = curr->next;
//	}
//	ft_printf("\n");
//	
//	//free the memory
//	curr = new_node;
//	while (curr != NULL)
//	{
//		t_list *temp = curr->next;
//		free(curr->content);
//		free(curr);
//		curr = temp;
//	}
//	return 0;
//}