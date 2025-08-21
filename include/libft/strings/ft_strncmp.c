/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:22:36 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/06/04 18:13:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"

/**
 * Compares up to `n` characters of the strings `s1` and `s2`.
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return 
 * An integer less than, equal to, or greater than zero,
 * depending on whether `s1` is lexicographically
 * less than, equal to, or greater than `s2`.
 * If the strings are equal up to the `n` characters,
 * the function returns 0.
 * @note
 * The comparison is done character by character up to `n` 
 * characters or until a null terminator is encountered.
 * If `n` is greater than the length of either string,
 * the comparison is limited to the actual length of the strings.
 */
// Implémentation de ft_strncmp (pour l'exemple)
int	ft_strncmp(const char *s1, const char *s2, t_size n)
{
	while (n--)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (0);
}
