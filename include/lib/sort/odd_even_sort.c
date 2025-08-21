/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_even_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:29:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:30:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	odd_pass(int *arr, int size, int *sorted)
{
	int	i;

	i = 1;
	while (i < size - 1)
	{
		if (arr[i] > arr[i + 1])
		{
			ft_swap(&arr[i], &arr[i + 1], sizeof(int));
			*sorted = 0;
		}
		i += 2;
	}
}

static void	even_pass(int *arr, int size, int *sorted)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (arr[i] > arr[i + 1])
		{
			ft_swap(&arr[i], &arr[i + 1], sizeof(int));
			*sorted = 0;
		}
		i += 2;
	}
}

void	odd_even_sort(int *arr, int size)
{
	int	sorted;

	if (!arr || size <= 1)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		odd_pass(arr, size, &sorted);
		even_pass(arr, size, &sorted);
	}
}
