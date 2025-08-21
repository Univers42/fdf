/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:02:28 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
/**
 * Creates a new string by duplicating the string `s`.
 * 
 * @param s The string to duplicate.
 * @return 
 * A pointer to the newly allocated string, 
 * or NULL if memory allocation fails.
 * 
 * @note 
 * The function allocates memory for a new string 
 * and copies the contents of `s` into it.
 * The newly allocated string is null-terminated.
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*cpy;

	dup = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	cpy = dup;
	while (*s)
		*dup++ = *s++;
	*dup = '\0';
	return (cpy);
}

//int main(void)
//{
//	char *str = ft_strdup("hello, world!");
//	if(!str)
//		return 1;
//	ft_printf("%s", str);
//	free(str);
//	return (0);
//}
