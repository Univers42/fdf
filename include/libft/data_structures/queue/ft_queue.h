/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:53:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_H
# define FT_QUEUE_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_queue_node
{
	void				*data;
	struct s_queue_node	*next;
}						t_queue_node;

typedef struct s_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
	size_t			size;
}					t_queue;

// Core functions
t_queue			*ft_queue_create(void);
void			ft_queue_destroy(t_queue *queue);
bool			ft_queue_enqueue(t_queue *queue, void *data);
void			*ft_queue_dequeue(t_queue *queue);

// Access functions
void			*ft_queue_front(t_queue *queue);
void			*ft_queue_rear(t_queue *queue);

// Utility functions
size_t			ft_queue_size(t_queue *queue);
bool			ft_queue_is_empty(t_queue *queue);
void			ft_queue_clear(t_queue *queue);

// Advanced functions
void			ft_queue_print_addresses(t_queue *queue);

#endif
