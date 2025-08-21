/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:17:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:13:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	simple_insertion_sort(int *arr, int n)
{
	int	i;
	int	j;
	int	key;

	i = 1;
	while (i < n)
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

static void	k_way_insertion_sort(int *arr, int n, int k)
{
	int	i;
	int	j;
	int	key;
	int	start;

	i = 1;
	while (i < n)
	{
		key = arr[i];
		if (i - k < 0)
			start = 0;
		else
			start = i - k;
		j = i - 1;
		while (j >= start && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		i++;
	}
}

void	ksort(int *arr, int n, int k)
{
	if (!arr || n <= 1 || k <= 0)
		return ;
	if (k >= n - 1)
	{
		simple_insertion_sort(arr, n);
		return ;
	}
	k_way_insertion_sort(arr, n, k);
	simple_insertion_sort(arr, n);
}
