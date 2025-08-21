/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:18:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 23:20:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Converts an uppercase letter to its lowercase equivalent.
 * 
 * @param c The character to convert.
 * @return 
 * The lowercase equivalent of `c` if `c` 
 * is an uppercase letter; otherwise, returns `c` unchanged.
 * 
 * @note 
 * If `c` is not an uppercase letter 
 * (i.e., not between 'A' and 'Z'), it is returned as is.
 * This function is typically used to standardize 
 * characters in a case-insensitive context.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}
