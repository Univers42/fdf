/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:25:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdint.h>
//#include "TDD/test.h"
/**
 * Calculates the length of the string `s`, 
 * excluding the null terminator.
 * 
 * @param s The string whose length is to be calculated.
 * @return The length of the string `s`.
 * 
 * @note 
 * The function iterates over the string until 
 * the null terminator is reached, 
 * counting the number of characters.
 */
//cause👇🏽👇🏽segmentation fault with strjoin
//size_t	ft_strlen(const char *s)
//{
//	const char	*cpy;
//
//	cpy = s;
//	while (*(s++))
//		;
//	return ((s - cpy) - 1);
//}

//size_t ft_strlen(const char *s)
//{
//    size_t len = 0;
//    while (s && *s++)
//        len++;
//    return len;
//}
//yo
//fr
//size_t ft_strlen(const char *s)
//{
//    int i = 0;
//    while(s[i])
//        i++;
//    return i;
//}
size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr++)
		;
	return ((ptr - s) - 1);
}
//size_t ft_strlen(const char *s)
//{
//    const char *start;
//    const size_t *word_ptr;
//    size_t word;
//    
//    start = s;
//    while(((uintptr_t)s  & (sizeof(size_t) - 1)) != 0)
//    {
//        if (*s == '\0')
//            return s - start;
//        s++;
//    }
//    word_ptr = (const size_t *)s;
//    while (1)
//    {
//        word = * word_ptr++;
//if(((word - 0x0101010101010101ULL) & -word & 0x8080808080808080ULL) != 0)
//            break;
//    }
//    s = (const char *)(word_ptr - 1);
//    while (*s)
//        s++;
//    return (s - start);
//}

//int main(void)
//{
//    char *lit = "hello world!";
//   	ft_printf("%ld", ft_strlen(lit));
//    return 0;
//}