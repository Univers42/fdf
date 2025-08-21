/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reserve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:05:51 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:58:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

bool	ft_vector_reserve(t_vector *vector, size_t capacity)
{
	if (!vector)
		return (false);
	if (capacity > vector->capacity)
		return (ft_vector_resize(vector, capacity));
	return (true);
}
