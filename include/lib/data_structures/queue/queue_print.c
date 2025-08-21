/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:50:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"
#include "../../stdio/ft_stdio.h"

void	ft_queue_print_addresses(t_queue *queue)
{
	t_queue_node	*current;

	if (!queue)
		return ;
	ft_printf("Queue (front -> rear): [");
	current = queue->front;
	while (current)
	{
		ft_printf("%p", current->data);
		current = current->next;
		if (current)
			ft_printf(", ");
	}
	ft_printf("]\n");
}
