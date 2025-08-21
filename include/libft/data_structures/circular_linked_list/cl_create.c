/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:24:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

t_circular_list	*ft_cl_create(void)
{
	t_circular_list	*list;

	list = malloc(sizeof(t_circular_list));
	if (!list)
		return (NULL);
	list->last = NULL;
	list->size = 0;
	return (list);
}
