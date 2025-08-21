/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:47:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:14:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

bool	ft_vector_insert(t_vector *vector, size_t index, void *element)
{
	size_t	i;

	if (!vector || index > vector->size || !element)
		return (false);
	if (vector->size >= vector->capacity)
	{
		if (!ft_vector_resize(vector, vector->capacity * VECTOR_GROWTH_FACTOR))
			return (false);
	}
	i = vector->size;
	while (i > index)
	{
		vector->data[i] = vector->data[i - 1];
		i--;
	}
	vector->data[index] = element;
	vector->size++;
	return (true);
}
