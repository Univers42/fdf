/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:17:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

/**
 * Initial: [64, 34, 25, 12, 22, 90]  pivot=90, i=-1

j=0: 64 < 90? YES → i=0, swap arr[0]↔arr[0] → [64, 34, 25, 12, 22, 90]
j=1: 34 < 90? YES → i=1, swap arr[1]↔arr[1] → [64, 34, 25, 12, 22, 90]  
j=2: 25 < 90? YES → i=2, swap arr[2]↔arr[2] → [64, 34, 25, 12, 22, 90]
j=3: 12 < 90? YES → i=3, swap arr[3]↔arr[3] → [64, 34, 25, 12, 22, 90]
j=4: 22 < 90? YES → i=4, swap arr[4]↔arr[4] → [64, 34, 25, 12, 22, 90]

Finally: swap pivot to position i+1=5 → [64, 34, 25, 12, 22, 90]
Work in-place - don't create new arrays
Use indices - low and high are array indices
Pivot positioning - the partition puts pivot in its final sorted position
Recursive calls - sort left and right subarrays separately
 */
static int	partition(int *array, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = array[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (array[j] < pivot)
		{
			i++;
			ft_swap(&array[i], &array[j], sizeof(int));
		}
		j++;
	}
	ft_swap(&array[i + 1], &array[high], sizeof(int));
	return (i + 1);
}

int	*ft_quick_sort(int *arr, int low, int high)
{
	int	pivot_index;

	if (low < high)
	{
		pivot_index = partition(arr, low, high);
		ft_quick_sort(arr, low, pivot_index - 1);
		ft_quick_sort(arr, pivot_index + 1, high);
	}
	return (arr);
}

//int main(void)
//{
//    int arr[] = {64, 34, 25, 12, 22, 90};
//    int size = 6;
//    
//   	ft_printf("Before sorting: ");
//    for (int i = 0; i < size; i++)
//       	ft_printf("%d ", arr[i]);
//   	ft_printf("\n");
//    
//    ft_quick_sort(arr, 0, size - 1);
//    
//   	ft_printf("After sorting: ");
//    for (int i = 0; i < size; i++)
//       	ft_printf("%d ", arr[i]);
//   	ft_printf("\n");
//    
//    return (0);
//}