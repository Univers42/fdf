/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:57:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	fill_left(int *arr, int *left, int l, int m)
{
	int	i;

	i = 0;
	while (i < m - l + 1)
	{
		left[i] = arr[l + i];
		i++;
	}
}

static void	fill_right(int *arr, int *right, int m, int r)
{
	int	i;

	i = 0;
	while (i < r - m)
	{
		right[i] = arr[m + 1 + i];
		i++;
	}
}

static void	merge_arrays(int *arr, int *left, int *right, int l)
{
	int	len1;
	int	len2;
	int	i;
	int	j;
	int	k;

	len1 = left[0];
	len2 = right[0];
	i = 1;
	j = 1;
	k = l;
	while (i <= len1 && j <= len2)
	{
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	while (i <= len1)
		arr[k++] = left[i++];
	while (j <= len2)
		arr[k++] = right[j++];
}

void	merge(int *arr, int l, int m, int r)
{
	int	len1;
	int	len2;
	int	*left;
	int	*right;

	len1 = m - l + 1;
	len2 = r - m;
	left = malloc((len1 + 1) * sizeof(int));
	right = malloc((len2 + 1) * sizeof(int));
	if (!left || !right)
	{
		if (left)
			free(left);
		if (right)
			free(right);
		return ;
	}
	left[0] = len1;
	right[0] = len2;
	fill_left(arr, left + 1, l, m);
	fill_right(arr, right + 1, m, r);
	merge_arrays(arr, left, right, l);
	free(left);
	free(right);
}

void	ft_merge_sort(int *arr, int l, int r)
{
	int	m;

	if (l < r)
	{
		m = l + (r - l) / 2;
		ft_merge_sort(arr, l, m);
		ft_merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

// Helper function to print array
//static void print_array(int *arr, int size)
//{
//    int i;
//    
//    i = 0;
//    while (i < size)
//    {
//       	ft_printf("%d ", arr[i]);
//        i++;
//    }
//   	ft_printf("\n");
//}
//
//int main(void)
//{
//    int arr[] = {2, 802, 24, 45, 66, 170, 75, 90};
//    int size = 8;
//	int l = 0;
//	int r = size - 1;
//	
//   	ft_printf("Original array: ");
//    print_array(arr, size);
//
//    ft_merge_sort(arr, l, r);
//
//   	ft_printf("Sorted array: ");
//    print_array(arr, size);
//
//    return (0);
//}