/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:14:08 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
/**
 * Locates the first occurrence of the character `c` in the string `s`.
 * 
 * @param s The string to search.
 * @param c The character to find.
 * @return
 * A pointer to the first occurrence of `c` in `s`, or NULL if `c` is not found.
 * 
 * @note 
 * The function searches the string `s` 
 * from the beginning until it finds the character `c`.
 * If `c` is not found, the function returns NULL. I
 * f `c` is the null terminator, the function
 * returns a pointer to the terminating null byte.
 */
char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}
//changes all the occurences of a word
//int main(void)
//{
//	char *ptr = 
//"kjshfjhs fhsjhdfhsa";
//	char *cpy;
//	char *found;
//
//	cpy = malloc(ft_strlen(ptr) + 1);
//	if(!cpy)
//		return 1;
//	ft_strlcpy(cpy, ptr, ft_strlen(ptr) + 1);
//	found = cpy;
//	while((found = ft_strchr(found, 'h')))
//	{
//		*found = 'H';
//		found++;
//	}	
//	ft_printf("original string: %s\n", ptr);
//	ft_printf("Modified string: %s\e\n", cpy);
//	free(cpy);
//	return 0;
//}