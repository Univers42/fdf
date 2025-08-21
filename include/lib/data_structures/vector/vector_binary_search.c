/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_binary_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:06:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:00:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

int	ft_vector_binary_search(t_vector *vec, void *target,
		int (*cmp)(const void *, const void *))
{
	size_t	left;
	size_t	right;
	size_t	mid;
	int		result;

	if (!vec || !target || !cmp || vec->size == 0)
		return (-1);
	left = 0;
	right = vec->size - 1;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		result = cmp(vec->data[mid], target);
		if (result == 0)
			return ((int)mid);
		else if (result < 0)
			left = mid + 1;
		else
		{
			if (mid == 0)
				break ;
			right = mid - 1;
		}
	}
	return (-1);
}
