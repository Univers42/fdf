/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:07:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static int	find_correct_position(int *arr, int size, int value)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (i < size)
	{
		if (arr[i] < value)
			pos++;
		i++;
	}
	return (pos);
}

static void	handle_duplicate_values(int *arr, int *pos, int value, int size)
{
	while (*pos < size && arr[*pos] == value)
		(*pos)++;
}

static int	process_cycle_item(int *arr, int size, int item, int start_pos)
{
	int	pos;
	int	writes;

	writes = 0;
	pos = find_correct_position(arr + start_pos + 1,
			size - start_pos - 1, item) + start_pos;
	if (pos == start_pos)
		return (0);
	handle_duplicate_values(arr, &pos, item, size);
	if (pos < size && item != arr[pos])
	{
		ft_swap(&arr[pos], &item, sizeof(int));
		writes++;
	}
	while (pos != start_pos && pos < size)
	{
		pos = find_correct_position(arr, size, item);
		handle_duplicate_values(arr, &pos, item, size);
		if (pos < size && item != arr[pos])
		{
			ft_swap(&arr[pos], &item, sizeof(int));
			writes++;
		}
	}
	return (writes);
}

int	ft_cycle_sort(int *arr, int size)
{
	int	writes;
	int	cycle_start;
	int	item;

	if (!arr || size <= 1)
		return (0);
	writes = 0;
	cycle_start = 0;
	while (cycle_start < size - 1)
	{
		item = arr[cycle_start];
		writes += process_cycle_item(arr, size, item, cycle_start);
		cycle_start++;
	}
	return (writes);
}

//int	main(void)
//{
//	int	arr2[] = {20, 30, 10, 40, 60, 50, 5};
//	int	size2;
//	int	writes;
//
//	size2 = 7;
//	ft_printf("Original array: ");
//	print_array(arr2, size2);
//	writes = ft_cycle_sort(arr2, size2);
//	ft_printf("Sorted array: ");
//	print_array(arr2, size2);
//	ft_printf("Total writes: %d\n", writes);
//	return (0);
//}
