/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_pop_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:33:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:54:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	*ft_vector_pop_back(t_vector *vector)
{
	void	*element;

	if (!vector || vector->size == 0)
		return (NULL);
	vector->size--;
	element = vector->data[vector->size];
	vector->data[vector->size] = NULL;
	return (element);
}
