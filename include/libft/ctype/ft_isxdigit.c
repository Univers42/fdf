/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 20:15:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/**
 * Checks if the given character is a hexadecimal digit.
 * A hexadecimal digit is 0-9, a-f, or A-F.
 * 
 * @param c The character to check (represented as an int)
 * @return 1 if the character is a hexadecimal digit, 0 otherwise.
 */
int	ft_isxdigit(int c)
{
	return (ft_isdigit(c)
		|| ((unsigned)(c - 'a') < 6)
		|| ((unsigned)(c - 'A') < 6));
}
