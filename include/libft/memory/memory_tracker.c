/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tracker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:51:10 by dlesieur          #+#    #+#             */
/*   Updated: 2025/05/28 17:50:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Create: memory_tracker.c
#include "ft_memory.h"

void	init_tracker(t_mem_tracker *tracker)
{
	tracker->ptrs = NULL;
	tracker->count = 0;
	tracker->capacity = 0;
}

void	*safe_malloc(t_mem_tracker *tracker, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (tracker->count >= tracker->capacity)
	{
		if (tracker->capacity == 0)
		{
			tracker->capacity = 10;
		}
		else
		{
			tracker->capacity *= 2;
		}
		size = tracker->capacity * sizeof(void *);
		tracker->ptrs = realloc(tracker->ptrs, size);
		if (!tracker->ptrs)
			return (NULL);
	}
	tracker->ptrs[tracker->count++] = ptr;
	return (ptr);
}

void	cleanup_all(t_mem_tracker *tracker)
{
	int	i;

	i = 0;
	while (i < tracker->count)
	{
		if (tracker->ptrs[i])
			free(tracker->ptrs[i]);
		i++;
	}
	if (tracker->ptrs)
		free(tracker->ptrs);
	tracker->count = 0;
	tracker->capacity = 0;
	tracker->ptrs = NULL;
}

//int main(int argc, char **argv)
//{
//    t_mem_tracker tracker;
//    
//}