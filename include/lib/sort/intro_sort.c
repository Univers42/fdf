/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:34:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:36:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"
#include <math.h>

static int	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] < pivot)
		{
			ft_swap(&arr[++i], &arr[j], sizeof(int));
		}
		j++;
	}
	ft_swap(&arr[i + 1], &arr[high], sizeof(int));
	return (i + 1);
}

static void	heapify(int *arr, int n, int i)
{
	int	largest;
	int	l;
	int	r;

	largest = i;
	l = 2 * i + 1;
	r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		ft_swap(&arr[i], &arr[largest], sizeof(int));
		heapify(arr, n, largest);
	}
}

static void	heap_sort_intro(int *arr, int n)
{
	int	i;

	i = n / 2 - 1;
	while (i >= 0)
	{
		heapify(arr, n, i);
		i--;
	}
	i = n - 1;
	while (i > 0)
	{
		ft_swap(&arr[0], &arr[i], sizeof(int));
		heapify(arr, i, 0);
		i--;
	}
}

static void	intro_sort_rec(int *arr, int low, int high, int depth_limit)
{
	int	p;

	if (high - low < 16)
	{
		insertion_sort(arr, low, high);
		return ;
	}
	if (depth_limit == 0)
	{
		heap_sort_intro(arr + low, high - low + 1);
		return ;
	}
	p = partition(arr, low, high);
	intro_sort_rec(arr, low, p - 1, depth_limit - 1);
	intro_sort_rec(arr, p + 1, high, depth_limit - 1);
}

void	intro_sort(int *arr, int size)
{
	int	depth_limit;

	if (!arr || size <= 1)
		return ;
	depth_limit = 2 * (int)log2(size);
	intro_sort_rec(arr, 0, size - 1, depth_limit);
}
