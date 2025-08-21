/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pancake_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 11:07:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	flip(int *arr, int i)
{
	int	start;
	int	end;

	start = 0;
	end = i;
	while (start < end)
	{
		ft_swap(&arr[start], &arr[end], sizeof(int));
		start++;
		end--;
	}
}

static int	find_max_index(int *arr, int size)
{
	int	max_idx;
	int	i;

	max_idx = 0;
	i = 1;
	while (i < size)
	{
		if (arr[i] > arr[max_idx])
			max_idx = i;
		i++;
	}
	return (max_idx);
}

void	pancake_sort(int *arr, int size)
{
	int	curr_size;
	int	max_idx;

	if (!arr || size <= 1)
		return ;
	curr_size = size;
	while (curr_size > 1)
	{
		max_idx = find_max_index(arr, curr_size);
		if (max_idx != curr_size - 1)
		{
			flip(arr, max_idx);
			flip(arr, curr_size - 1);
		}
		curr_size--;
	}
}
