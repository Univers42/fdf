/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:43:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 23:29:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//#include "TDD/test.h"
/**
 * Compares the first `n` bytes of two memory areas `s1` and `s2`.
 * 
 * @param s1 The first memory area to compare.
 * @param s2 The second memory area to compare.
 * @param n The number of bytes to compare.
 * @return 
 * An integer less than, equal to, or greater 
 * than zero if the first `n` bytes of `s1` 
 * are found to be less than, equal to, or greater than 
 * those of `s2`, respectively.
 * 
 * @note The comparison is done byte-by-byte, 
 * and the result is based on the difference between 
 * the first differing byte. If no differences are found, zero is returned.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
