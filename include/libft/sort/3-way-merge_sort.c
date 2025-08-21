/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-way-merge_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:53:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:53:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	three_way_merge_sort(int *arr, int size)
{
	int	*temp;
	int	bounds[2];

	if (!arr || size <= 1)
		return ;
	temp = malloc(size * sizeof(int));
	if (!temp)
		return ;
	bounds[0] = 0;
	bounds[1] = size - 1;
	three_way_merge_sort_rec(arr, bounds, temp);
	free(temp);
}
