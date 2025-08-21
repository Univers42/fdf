/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:46:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	count_elements(int *arr, int *count, int size, int min)
{
	int	i;

	i = 0;
	while (i < size)
	{
		count[arr[i] - min]++;
		i++;
	}
}

static void	place_elements(int *arr, int *count, int range, int min)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < range)
	{
		while (count[i] > 0)
		{
			arr[j++] = i + min;
			count[i]--;
		}
		i++;
	}
}

void	counting_sort(int *arr, int size)
{
	int	*count;
	int	min;
	int	max;
	int	range;

	if (!arr || size <= 1)
		return ;
	min = get_min(arr, size);
	max = get_max(arr, size);
	range = max - min + 1;
	count = calloc(range, sizeof(int));
	if (!count)
		return ;
	count_elements(arr, count, size, min);
	place_elements(arr, count, range, min);
	free(count);
}

//int	main(void)
//{
//    int	arr[] = {4, 2, 2, 8, 3, 3, 1};
//    int	size = sizeof(arr) / sizeof(arr[0]);
//    int	i;
//
//   	ft_printf("Before sorting:\n");
//    i = 0;
//    while (i < size)
//    {
//       	ft_printf("%d ", arr[i]);
//        i++;
//    }
//   	ft_printf("\n");
//    collection_sort(arr, size);
//   	ft_printf("After sorting:\n");
//    i = 0;
//    while (i < size)
//    {
//       	ft_printf("%d ", arr[i]);
//        i++;
//    }
//   	ft_printf("\n");
//    return (0);
//}