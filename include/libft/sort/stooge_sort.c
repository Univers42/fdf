/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stooge_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:22:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	stooge_sort_rec(int *arr, int l, int h)
{
	int	t;

	if (l >= h)
		return ;
	if (arr[l] > arr[h])
		ft_swap(&arr[l], &arr[h], sizeof(int));
	if (h - l + 1 > 2)
	{
		t = (h - l + 1) / 3;
		stooge_sort_rec(arr, l, h - t);
		stooge_sort_rec(arr, l + t, h);
		stooge_sort_rec(arr, l, h - t);
	}
}

void	stooge_sort(int *arr, int size)
{
	if (!arr || size <= 1)
		return ;
	stooge_sort_rec(arr, 0, size - 1);
}
