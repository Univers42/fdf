/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:12:10 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
/**@LEARNED : 
 * indexed mapping have no connection or not 
 * related to hash mapping functions, it indicates that a function
 * will process elements with their `indices` , 
 * allowing for operations that depend
 * on both value and its position
 * apply the function 'f' to each character of the string
 * passing its indice like a first argument, 
 * and its proper character as second argument
 * We create  a new string using malloc(3) 
 * to retrieve the successives mapped of
 * f applicacion.
 * @param s the string ....
 * @param f the function to apply to each character
 * @return the newly string modified by 
 * the function and NULL if memoria failed
 */

/**
 * Applies the function `f` to each character of the string `s`, 
 * passing the index of the character
 * as the first argument and the character itself as the second argument. 
 * Returns a new string that
 * contains the modified characters.
 * 
 * @param s The string to iterate over.
 * @param f The function to apply to each character
 * @return 
 * A new string with the modified characters, 
 * or NULL if memory allocation fails.
 * 
 * @note The function allocates memory for a new string, 
 * which is then populated with the results
 *       of applying `f` to each character of `s`. 
 * The string is null-terminated. If memory allocation
 *       fails, NULL is returned.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			i;
	char			*mapped;
	char			*start;

	if (!s || !f)
		return (NULL);
	mapped = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mapped)
		return (NULL);
	i = 0;
	start = mapped;
	while (*s)
	{
		*mapped++ = f(i, *s++);
		i++;
	}
	*mapped = '\0';
	return (start);
}
/**
 * we're building a system that handle license keys for a software application.
 * Each license key is stored as plain string, but you need to: 
 * Convert all alphabetic characters to uppercase.
 */
//static char license_key_formatter(unsigned int i, char c)
//{
//    if (c >= 'a' && c <= 'z')
//        c -= 32; // Convert to uppercase
//    if (i > 0 && i % 5 == 4) // Insert a dash after every 4 characters
//        return '-';
//    return c;
//}

//int main(void)
//{
//	char *license_key = "abcd1234efgh5678ijkl"; 
//	char *formatted_key = ft_strmapi(license_key, license_key_formatter);
//	if(formatted_key)
//	{
//		ft_printf("Original key: %s\n", license_key);
//		ft_printf("Formatted key:  %s\n", formatted_key);
//		free(formatted_key);
//	}
//	else
//		ft_printf("Error formatting license key.\n");
//	return (0);
//}