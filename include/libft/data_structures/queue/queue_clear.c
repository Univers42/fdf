/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:52:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

void	ft_queue_clear(t_queue *queue)
{
	t_queue_node	*current;
	t_queue_node	*next;

	if (!queue)
		return ;
	current = queue->front;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
}
