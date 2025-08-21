/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:38:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:00:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

bool	ft_vector_resize(t_vector *vector, size_t new_capacity)
{
	void	**new_data;
	size_t	i;

	if (!vector || new_capacity < vector->size)
		return (false);
	new_data = malloc(sizeof(void *) * new_capacity);
	if (!new_data)
		return (false);
	i = 0;
	while (i < vector->size)
	{
		new_data[i] = vector->data[i];
		i++;
	}
	free(vector->data);
	vector->data = new_data;
	vector->capacity = new_capacity;
	return (true);
}
