/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:29:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:58:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include <stdbool.h>

bool	ft_vector_add_back(t_vector *vector, void *element)
{
	if (!vector)
		return (false);
	if (vector->size >= vector->capacity)
	{
		if (!ft_vector_resize(vector, vector->capacity * VECTOR_GROWTH_FACTOR))
			return (false);
	}
	vector->data[vector->size] = element;
	vector->size++;
	return (true);
}
