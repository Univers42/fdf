/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:19:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../strings/ft_string.h"

/**
 * Trims the characters from both ends of 
 * the string `s1` that belong to 
 * the set of characters specified in `set`.
 * 
 * @param s1 The string to be trimmed.
 * @param set The set of characters to be trimmed from both ends of `s1`.
 * @return 
 * A new string that is a trimmed version of `s1`,
 * or NULL if memory allocation fails.
 * 
 * @note 
 * The function calculates the length of the leading and 
 * trailing characters that match with `set`.
 * It then creates a new string that contains the substring 
 *from `s1`, excluding the matching characters.
 * If `set` is NULL or `s1` is NULL, the behavior is undefined. 
 * If no characters need to be trimmed, 
 *       a copy of `s1` will be returned.
 */
char	*ft_strtrim(const char *s1, const char *set)
{
	char	*new_string;
	size_t	start;
	size_t	end;
	size_t	new_len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	new_len = end - start;
	new_string = malloc(new_len +1);
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1 + start, new_len + 1);
	return (new_string);
}
// TODO test
//int main()
//{
//	char *s1 = "   hello world!   ";
//	char *set = " ";
//	char *trimmed;
//	
//	trimmed = ft_strtrim(s1, set);
//	if (trimmed)
//	{
//		ft_printf("old string : '%s'\n", s1);
//		ft_printf("new_string : '%s'\n", trimmed);
//		free(trimmed);
//		return 0;
//	}
//	return 1;
//}