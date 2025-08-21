/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tim_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:12:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	tim_sort_runs(int *arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		insertion_sort(arr, i, ft_min(i + RUN - 1, n - 1));
		i += RUN;
	}
}

static void	tim_sort_merge(int *arr, int n)
{
	int	size;
	int	left;
	int	mid;
	int	right;

	size = RUN;
	while (size < n)
	{
		left = 0;
		while (left < n - 1)
		{
			mid = left + size - 1;
			right = ft_min(left + size * 2 - 1, n - 1);
			if (mid < right)
				merge(arr, left, mid, right);
			left += size * 2;
		}
		size *= 2;
	}
}

void	tim_sort(int *arr, int n)
{
	tim_sort_runs(arr, n);
	tim_sort_merge(arr, n);
}
//
//int	main(void)
//{
//	int	arr[] = {2, 802, 24, 45, 66, 170, 75, 90};
//	int	size;
//
//	size = 8;
//	ft_printf("Original array: ");
//	print_array(arr, size);
//	tim_sort(arr, size);
//	ft_printf("Sorted array: ");
//	print_array(arr, size);
//	return (0);
//}