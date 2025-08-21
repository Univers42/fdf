/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:42:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:17:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_ctype.h"

/**
 * @param i optional depending on implementation
 */
void	skip_spaces(int *i, int size, char *str)
{
	if (i != NULL)
	{
		while (*i < size && ft_isspace(str[*i]))
			(*i)++;
	}
}
