/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnome_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

// Gnome sort implementation
void	ft_gnome_sort(int *arr, int size)
{
	int	index;

	if (!arr || size <= 1)
		return ;
	index = 0;
	while (index < size)
	{
		if (index == 0)
			index++;
		if (arr[index] >= arr[index - 1])
			index++;
		else
		{
			ft_swap(&arr[index], &arr[index - 1], sizeof(int));
			index--;
		}
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