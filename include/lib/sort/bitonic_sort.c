/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitonic_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:18:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:30:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	bitonic_merge(int *arr, int low, int cnt, int dir)
{
	int	i;
	int	k;

	if (cnt > 1)
	{
		k = cnt / 2;
		i = low;
		while (i < low + k)
		{
			if ((dir && arr[i] > arr[i + k]) || (!dir && arr[i] < arr[i + k]))
				ft_swap(&arr[i], &arr[i + k], sizeof(int));
			i++;
		}
		bitonic_merge(arr, low, k, dir);
		bitonic_merge(arr, low + k, k, dir);
	}
}

static void	bitonic_sort_rec(int *arr, int low, int cnt, int dir)
{
	int	k;

	if (cnt > 1)
	{
		k = cnt / 2;
		bitonic_sort_rec(arr, low, k, 1);
		bitonic_sort_rec(arr, low + k, k, 0);
		bitonic_merge(arr, low, cnt, dir);
	}
}

static void	copy_and_pad_array(int *arr, int *padded_arr, int size,
				int power_of_2)
{
	int	i;

	i = -1;
	while (++i < size)
		padded_arr[i] = arr[i];
	i = -1;
	while (++i < power_of_2)
		padded_arr[i] = 2147483647;
}

static void	copy_back_array(int *arr, int *padded_arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		arr[i] = padded_arr[i];
}

void	bitonic_sort(int *arr, int size)
{
	int	power_of_2;
	int	*padded_arr;

	if (!arr || size <= 1)
		return ;
	power_of_2 = 1;
	while (power_of_2 < size)
		power_of_2 *= 2;
	if (power_of_2 == size)
	{
		bitonic_sort_rec(arr, 0, size, 1);
		return ;
	}
	padded_arr = malloc(power_of_2 * sizeof(int));
	if (!padded_arr)
		return ;
	copy_and_pad_array(arr, padded_arr, size, power_of_2);
	bitonic_sort_rec(padded_arr, 0, power_of_2, 1);
	copy_back_array(arr, padded_arr, size);
	free(padded_arr);
}
