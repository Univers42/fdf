/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:41:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include "TDD/test.h"
/**
 * Clears and frees the entire list starting from the node `lst`,
 * by applying the `del` function to each 
 * node's content and then freeing the node.
 * 
 * @param lst A double pointer to the first node of the list.
 * @param del A pointer fn to delete the content of each node.
 * 
 * @return Nothing.
 * 
 * @note
 * The function will iterate over the entire list, 
 * apply `del` to each node's content, 
 * and free the memory of each node. After clearing, 
 * the `lst` pointer is set to NULL.
 */

//static void delete(void *content)
//{
//	free(content);	
//}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		curr = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(curr, del);
	}
}

//int main(int argc, char **argv)
//{
//	if(argc != 2)
//		return 1;
//	int size = ft_atoi(argv[1]);
//	if (size < 0)
//		return 2;
//	t_list *lst = ft_lstnew(ft_strdup("GROOOOOOT"));
//	if(!lst)
//		return 3;
//	for(int i = 0; i < size ; i++)
//	{
//		t_list *new_node = ft_lstnew(ft_strdup("BODY"));
//		if(!new_node)
//		{
//			ft_lstclear(&lst, &delete);
//			return 4;
//		}
//		ft_lstadd_back(&lst, new_node);
//	}
//	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("TAIL")));
//	ft_printf("Size Before ft_lstclear(): %d\n", ft_lstsize(lst));
//	ft_lstclear(&lst, &delete);
//	ft_printf("Size after ft_lstclear(): %d\n", lst ? ft_lstsize(lst) : 0);
//	return 0;
//}
