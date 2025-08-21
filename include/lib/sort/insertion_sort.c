/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:57:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:44:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	insertion_sort(int arr[], int left, int right)
{
	int	i;
	int	j;
	int	key;

	i = left + 1;
	while (i <= right)
	{
		key = arr[i];
		j = i - 1;
		while (j >= left && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		i++;
	}
}

//int main(void)
//{
//    int arr[7] = {25 ,0, 5, 1, 50, 42, 40};
//    int size = 7;
//    print_array(arr, size);
//    insertion_sort(arr, size);
//    print_array(arr, size);
//    return (0);   
//}