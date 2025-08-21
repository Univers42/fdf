/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:59:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
/**
 * Scans the first `n` bytes of the memory area pointed to by `s`
 * for the first occurrence of the byte `c`.
 * 
 * @param s Pointer to the memory area to be searched.
 * @param c The byte to search for.
 * @param n The number of bytes to search.
 * @return A pointer to the first occurrence of `c` in `s`, 
 * or NULL if `c` is not found.
 * 
 * @note The search is done byte-by-byte and the comparison 
 * is performed using unsigned char values.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if ((unsigned char)c == (unsigned char)*str)
			return ((void *)str);
		str++;
	}
	return (NULL);
}

//int main(void)
//{
//	char str[] = "hello woarld!";
//	int arr[] = {1,561,21,54,65,41,315,112,12};
//char *result = (char *)ft_memchr((char *)str, 97, ft_strlen(str));
//int *ptr = (int *)ft_memchr((int *)arr, 65, sizeof(arr));
//printf("result - str = [%s - %s] => %ld\n",result, str, result - str);
// if (ptr)
//	ft_printf("Value %c found in array at index: [%ld]\n", *ptr, ptr - arr);
//    else
//       	ft_printf("Value '0' not found in array.\n");
//}