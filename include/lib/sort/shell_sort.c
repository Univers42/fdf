/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:43:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:43:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	shell_sort(int *arr, int size)
{
	int	gap;
	int	i;
	int	j;
	int	temp;

	if (!arr || size <= 1)
		return ;
	gap = size / 2;
	while (gap > 0)
	{
		i = gap;
		while (i < size)
		{
			temp = arr[i];
			j = i;
			while (j >= gap && arr[j - gap] > temp)
			{
				arr[j] = arr[j - gap];
				j -= gap;
			}
			arr[j] = temp;
			i++;
		}
		gap /= 2;
	}
}
