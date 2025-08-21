/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:47:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:14:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	*ft_vector_remove(t_vector *vector, size_t index)
{
	void	*element;
	size_t	i;

	if (!vector || index >= vector->size)
		return (NULL);
	element = vector->data[index];
	i = index;
	while (i < vector->size - 1)
	{
		vector->data[i] = vector->data[i + 1];
		i++;
	}
	vector->size--;
	vector->data[vector->size] = NULL;
	return (element);
}
