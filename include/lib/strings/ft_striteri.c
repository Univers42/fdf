/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:30:16 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/01/26 21:00:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
//    size_t len = 0;
//    while (s[len])
//        len++;
//    return (len);
//}
//
//
//static void apply_toupper(unsigned int index, char *c) {
//    if (*c >= 'a' && *c <= 'z')
//        *c -= 32; // Convert to uppercase
//}
//static size_t ft_strlen(char *s) {

/**
 * Iterates over each character in the string `s`
 * and applies the function `f` to each character.
 * 
 * @param s The string to iterate over.
 * @param f The function to apply to each character.
 * 			The function receives the index of the character
 *          and a pointer to the character itself.
 * @return Nothing.
 * 
 * @details 
 * This function goes through each character of the string 
 * `s` and calls `f` on each character, 
 * passing its index and a pointer to the character.
 * The string is modified in place, if necessary.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;
	size_t	len;

	if (!s || !f)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}
