/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:57:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:22:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

int	*ft_bubble_sort(int *arr, int size)
{
	int		i;
	int		j;
	bool	swapped;

	if (!arr || size <= 1)
		return (arr);
	i = 0;
	while (i < size - 1)
	{
		swapped = false;
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				ft_swap(&arr[j], &arr[j + 1], sizeof(int));
				swapped = true;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
	return (arr);
}
