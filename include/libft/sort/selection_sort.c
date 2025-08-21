/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:58:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 11:13:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	ft_selection_sort(int *arr, int n)
{
	int	i;
	int	j;
	int	min_idx;

	if (!arr || n <= 1)
		return ;
	i = 0;
	while (i < n - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < n)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
			j++;
		}
		if (min_idx != i)
			ft_swap(&arr[min_idx], &arr[i], sizeof(int));
		i++;
	}
}
