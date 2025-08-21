/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:04:20 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/06/04 14:15:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
//#include "TDD/test.h"
/**
 * Concatenates the string `s2` to the end of 
 * the string `s1` and returns a new string.
 * 
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate to `s1`.
 * @return
 * A new string that is the result of `s1` 
 * followed by `s2`, or NULL if memory allocation fails.
 * 
 * @note 
 * The function allocates memory for 
 * the new string and copies both `s1` and `s2` into it.
 * The new string is null-terminated.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len1)
		new_str[i] = s1[i];
	j = -1;
	while (++j < len2)
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	return (new_str);
}
