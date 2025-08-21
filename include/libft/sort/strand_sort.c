/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strand_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:02:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:23:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	merge_helper(int *result, int *a, int a_size, int *counters)
{
	while (counters[0] < a_size && counters[1] < counters[3])
	{
		if (a[counters[0]] <= counters[4])
			result[counters[2]++] = a[counters[0]++];
		else
			result[counters[2]++] = counters[4]++;
	}
	while (counters[0] < a_size)
		result[counters[2]++] = a[counters[0]++];
	while (counters[1] < counters[3])
		result[counters[2]++] = counters[4]++;
}

static void	merge_arrays(int *result, int *a, int a_size, int *b)
{
	int	counters[5];

	counters[0] = 0;
	counters[1] = 0;
	counters[2] = 0;
	counters[3] = b[0];
	counters[4] = (int)(intptr_t)&b[1];
	merge_helper(result, a, a_size, counters);
}

static int	extract_strand(int *arr, int *used, int size, int *strand)
{
	int	last;
	int	count;
	int	i;

	last = -2147483648;
	count = 0;
	i = 0;
	while (i < size)
	{
		if (!used[i] && arr[i] >= last)
		{
			strand[count++] = arr[i];
			last = arr[i];
			used[i] = 1;
		}
		i++;
	}
	return (count);
}

static void	process_strand(int **result, int *result_size, int *strand,
	int strand_size)
{
	int	*merged;
	int	*b_data;

	b_data = malloc((strand_size + 1) * sizeof(int));
	b_data[0] = strand_size;
	memcpy(&b_data[1], strand, strand_size * sizeof(int));
	merged = malloc((*result_size + strand_size) * sizeof(int));
	merge_arrays(merged, *result, *result_size, b_data);
	memcpy(*result, merged, (*result_size + strand_size) * sizeof(int));
	*result_size += strand_size;
	free(b_data);
	free(merged);
}

void	strand_sort(int *arr, int size)
{
	int	*used;
	int	*result;
	int	result_size;
	int	*strand;
	int	strand_size;

	used = calloc(size, sizeof(int));
	result = malloc(size * sizeof(int));
	result_size = 0;
	while (result_size < size)
	{
		strand = malloc(size * sizeof(int));
		strand_size = extract_strand(arr, used, size, strand);
		process_strand(&result, &result_size, strand, strand_size);
		free(strand);
	}
	memcpy(arr, result, size * sizeof(int));
	free(result);
	free(used);
}
