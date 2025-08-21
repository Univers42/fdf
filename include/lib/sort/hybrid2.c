/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hybrid2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:35:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	binary_search_and_tag(int *sorted, int *arr, int size)
{
	int	i;
	int	left;
	int	right;
	int	mid;

	i = 0;
	while (i < size)
	{
		left = 0;
		right = size - 1;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (sorted[mid] == arr[i])
			{
				arr[i] = mid;
				break ;
			}
			else if (sorted[mid] < arr[i])
				left = mid + 1;
			else
				right = mid - 1;
		}
		i++;
	}
}

static void	tag_array(int *arr, int size, int *tag_to_value)
{
	int	*sorted;
	int	i;

	sorted = malloc(size * sizeof(int));
	memcpy(sorted, arr, size * sizeof(int));
	qsort(sorted, size, sizeof(int), cmp_int);
	i = 0;
	while (i < size)
	{
		tag_to_value[i] = sorted[i];
		i++;
	}
	binary_search_and_tag(sorted, arr, size);
	free(sorted);
}

static void	process_chunk(int *arr, int *result, int *used, int chunk_params[4])
{
	int	tag;
	int	i;

	tag = chunk_params[0];
	while (tag < chunk_params[1])
	{
		i = 0;
		while (i < chunk_params[3])
		{
			if (!used[i] && arr[i] == tag)
			{
				result[chunk_params[2]++] = arr[i];
				used[i] = 1;
				break ;
			}
			i++;
		}
		tag++;
	}
}

static void	greedy_chunk_sort(int *arr, int size, int chunk_count)
{
	int	chunk_size;
	int	*result;
	int	*used;
	int	c;
	int	chunk_params[4];

	chunk_size = (size + chunk_count - 1) / chunk_count;
	result = malloc(size * sizeof(int));
	used = calloc(size, sizeof(int));
	chunk_params[2] = 0;
	chunk_params[3] = size;
	c = 0;
	while (c < chunk_count)
	{
		chunk_params[0] = c * chunk_size;
		chunk_params[1] = (c + 1) * chunk_size;
		if (chunk_params[1] > size)
			chunk_params[1] = size;
		process_chunk(arr, result, used, chunk_params);
		c++;
	}
	memcpy(arr, result, size * sizeof(int));
	free(result);
	free(used);
}

void	hybrid2_sort(int *arr, int size, int *tag_to_value)
{
	int	i;
	int	key;
	int	j;

	tag_array(arr, size, tag_to_value);
	if (size <= 5)
	{
		i = 1;
		while (i < size)
		{
			key = arr[i];
			j = i - 1;
			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
			i++;
		}
	}
	else if (size <= 100)
		greedy_chunk_sort(arr, size, 5);
	else
		greedy_chunk_sort(arr, size, 11);
}
