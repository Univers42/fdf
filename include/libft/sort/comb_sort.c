/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comb_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static int	get_next_gap(int gap)
{
	gap = (gap * 10) / 13;
	if (gap < 1)
		return (1);
	return (gap);
}

void	comb_sort(int *arr, int size)
{
	int	gap;
	int	swapped;
	int	i;

	if (!arr || size <= 1)
		return ;
	gap = size;
	swapped = 1;
	while (gap != 1 || swapped)
	{
		gap = get_next_gap(gap);
		swapped = 0;
		i = 0;
		while (i < size - gap)
		{
			if (arr[i] > arr[i + gap])
			{
				ft_swap(&arr[i], &arr[i + gap], sizeof(int));
				swapped = 1;
			}
			i++;
		}
	}
}

//int	main(void)
//{
//    int	arr[] = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
//    int	size = sizeof(arr) / sizeof(arr[0]);
//
//   	ft_printf("Original array: ");
//    print_array(arr, size);
//    comb_sort(arr, size);
//   	ft_printf("Sorted array:   ");
//    print_array(arr, size);
//    return (0);
//}
