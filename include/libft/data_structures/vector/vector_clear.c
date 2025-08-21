/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:47:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:00:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	ft_vector_clear(t_vector *vector)
{
	size_t	i;

	if (!vector)
		return ;
	i = -1;
	while (++i < vector->size)
		vector->data[i] = NULL;
	vector->size = 0;
}
