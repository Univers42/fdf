/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:22:24 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:20:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"
#include "../data_structures/data_structures.h"
#include "../stdio/ft_stdio.h"

//void print_list(t_ps *)
//{
//    t_list *list;
//    int *value;
//
//    if (!ps || !ps->head_a)
//    {
//        ft_printf("Stack A: (empty)\n");
//        return ;
//    }
//    ft_printf("stack A: ");
//    list = ps->head_a;
//    while (list != NULL)
//    {
//        value = (int *)list->content;
//        if (value)
//        {
//            // Show: [value] at node_address -> next_node_address
//            ft_printf(GREEN"["MAGENTA"["BRIGHT_CYAN"[%d] 
//"BLUE"at %p"MAGENTA"]"RESET, *value, (void*)list);
//            if (list->next)
//                ft_printf(RED" -> [next: %p]"GREEN"] 
//\n"RESET, (void*)list->next);
//            else
//                ft_printf(RED" -> [next: NULL"GREEN"]"RESET);
//        }
//        else
//            ft_printf("[[NULL] at %p]", (void*)list);
//        
//        if (list->next)
//            ft_printf(" -> ");
//        list = list->next;
//    }
//    ft_printf("\n");
//}
//
void	ft_print_list(t_list *list)
{
	t_list	*current;

	if (!list)
	{
		ft_printf("List is NULL\n");
		return ;
	}
	current = list;
	ft_printf("List: ");
	while (current)
	{
		if (current->content)
			ft_printf("[%s] -> ", (char *)current->content);
		else
			ft_printf("[NULL] -> ");
		current = current->next;
	}
	ft_printf("NULL\n");
}

void	ft_print_list_addresses(t_list *list)
{
	t_list	*current;

	if (!list)
	{
		ft_printf("List is NULL\n");
		return ;
	}
	current = list;
	ft_printf("List addresses: ");
	while (current)
	{
		ft_printf("[%p: %p] -> ", (void *)current,
			(void *)current->content);
		current = current->next;
	}
	ft_printf("NULL\n");
}
