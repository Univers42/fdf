/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:42:41 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/06/04 18:13:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
/**
 * Extracts a substring from the string `s`, 
 * starting at index `start` and up to `len` characters.
 * 
 * @param s The string from which the substring is extracted.
 * @param start The index where the substring starts in `s`.
 * @param len The maximum length of the substring to extract.
 * @return
 * A newly allocated string containing the extracted substring,
 * or NULL if memory allocation fails.
 * 
 * @note 
 * If `start` is greater than or equal to the length 
 * of `s`, the function returns an empty string.
 * If `len` exceeds the remaining length of 
 * `s` from `start`, the function will only copy the characters
 * available up to the end of `s`.
 */
char	*ft_substr(char const *s, unsigned int start, t_size len)
{
	char	*str;
	t_size	s_len;
	t_size	substring_len;

	if (NULL == s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	substring_len = s_len - start;
	if (len > substring_len)
		len = substring_len;
	str = malloc(len + 1);
	if (NULL == str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
