/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:25:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

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

void	heap_sort(int *arr, int size)
{
	int	i;

	if (!arr || size <= 1)
		return ;
	i = size / 2 - 1;
	while (i >= 0)
	{
		heapify(arr, size, i);
		i--;
	}
	i = size - 1;
	while (i > 0)
	{
		ft_swap(&arr[0], &arr[i], sizeof(int));
		heapify(arr, i, 0);
		i--;
	}
}

//int	main(void)
//{
//	int	arr[] = {34, 2, 10, -9, 50, 3, 40, 7};
//	int	size = 8;
//
//	ft_printf("Original array: ");
//	print_array(arr, size);
//	ft_gnome_sort(arr, size);
//	ft_printf("Sorted array: ");
//	print_array(arr, size);
//	return (0);
//}