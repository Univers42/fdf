/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:32:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

size_t	ft_cl_size(t_circular_list *list)
{
	if (!list)
		return (0);
	return (list->size);
}

bool	ft_cl_is_empty(t_circular_list *list)
{
	if (!list || list->size == 0)
		return (true);
	return (false);
}

void	ft_cl_clear(t_circular_list *list)
{
	t_cl_node	*current;
	t_cl_node	*next;
	size_t		i;

	if (!list || ft_cl_is_empty(list))
		return ;
	current = list->last->next;
	i = -1;
	while (++i < list->size)
	{
		next = current->next;
		free(current);
		current = next;
	}
	list->last = NULL;
	list->size = 0;
}

void	ft_cl_rotate_forward(t_circular_list *list, size_t steps)
{
	size_t	i;

	if (!list || ft_cl_is_empty(list) || list->size == 1)
		return ;
	steps = steps % list->size;
	i = -1;
	while (++i < steps)
		list->last = list->last->next;
}

void	ft_cl_rotate_backward(t_circular_list *list, size_t steps)
{
	size_t		i;
	size_t		actual_steps;

	if (!list || ft_cl_is_empty(list) || list->size == 1)
		return ;
	steps = steps % list->size;
	actual_steps = list->size - steps;
	i = -1;
	while (++i < actual_steps)
		list->last = list->last->next;
}
