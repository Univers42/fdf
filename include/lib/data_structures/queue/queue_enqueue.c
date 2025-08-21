/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_enqueue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:51:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

bool	ft_queue_enqueue(t_queue *queue, void *data)
{
	t_queue_node	*new_node;

	if (!queue)
		return (false);
	new_node = malloc(sizeof(t_queue_node));
	if (!new_node)
		return (false);
	new_node->data = data;
	new_node->next = NULL;
	if (ft_queue_is_empty(queue))
	{
		queue->front = new_node;
		queue->rear = new_node;
	}
	else
	{
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
	queue->size++;
	return (true);
}
