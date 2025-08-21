/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:42:51 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:55:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

bool	ft_vector_set(t_vector *vector, size_t index, void *content)
{
	if (!vector || index >= vector->size || !content)
		return (false);
	vector->data[index] = content;
	return (true);
}
