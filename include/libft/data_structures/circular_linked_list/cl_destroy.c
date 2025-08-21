/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:24:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"

void	ft_cl_destroy(t_circular_list *list)
{
	if (!list)
		return ;
	ft_cl_clear(list);
	free(list);
}
