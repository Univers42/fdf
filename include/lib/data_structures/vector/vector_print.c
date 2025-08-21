/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:54:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:56:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "../../stdio/ft_stdio.h"

void	ft_vector_print_addresses(t_vector *vector)
{
	void	**ptr;
	void	**end;

	if (!vector)
		return ;
	ptr = vector->data;
	end = vector->data + vector->size;
	ft_printf("[");
	while (ptr < end)
	{
		ft_printf("%p", *ptr);
		ptr++;
		if (ptr < end)
			ft_printf(", ");
	}
	ft_printf("]\n");
}
