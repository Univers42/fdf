/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hybrid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:50:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	tag_array_sort(int *arr, int size)
{
	int	*sorted;
	int	i;
	int	j;

	sorted = malloc(size * sizeof(int));
	i = 0;
	while (i < size)
	{
		sorted[i] = arr[i];
		i++;
	}
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (sorted[i] > sorted[j])
				ft_swap(&sorted[i], &sorted[j], sizeof(int));
			j++;
		}
		i++;
	}
	free(sorted);
}

static void	radix_sort_hybrid(int *arr, int size)
{
	int	max;
	int	max_bits;
	int	bit;

	max = get_max(arr, size);
	max_bits = 0;
	while ((max >> max_bits) != 0)
		max_bits++;
	bit = 0;
	while (bit < max_bits)
	{
		counting_sort(arr, size);
		bit++;
	}
}

static void	insertion_sort_hybrid(int *arr, int size)
{
	int	i;
	int	key;
	int	j;

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

void	hybrid_sort(int *arr, int size)
{
	tag_array_sort(arr, size);
	if (size <= 5)
		insertion_sort_hybrid(arr, size);
	else
		radix_sort_hybrid(arr, size);
}
