/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:33:34 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
/**
 * Copies up to `dsize - 1` characters from the 
 * string `src` to `dst`, ensuring that the
 * destination buffer is null-terminated. 
 * If `dsize` is less than or equal to the length of `src`,
 * the string will be truncated.
 * 
 * @param dst The destination buffer where the string will be copied.
 * @param src The source string to copy from.
 * @param dsize The size of the destination buffer `dst`.
 * @return The length of the source string `src`.
 * 
 * @note 
 * The function copies at most `dsize - 1` characters 
 * from `src` to `dst`, ensuring that the      
 * resulting string in `dst` is null-terminated. 
 * If `dsize` is greater than the length of `src`,
 * the function copies the entire string and adds
 *  a null terminator. If `dsize` is smaller than
 * or equal to the length of `src`, the string is
 *  truncated and the null terminator is not added.
 */
t_size	ft_strlcpy(char *dst, const char *src, t_size dsize)
{
	t_size	i;

	i = 0;
	if (dsize > 0)
	{
		while (src[i] != '\0' && i < dsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
//int main(void)
//{
//	char *ptr_to_be_copied;
//	char *src = "hello world!";
//	ft_printf("%ld,\n %ld\n", sizeof(src), ft_strlen(src));
//	ft_printf("%ld\n",ft_strlcpy(ptr_to_be_copied, src, ft_strlen(src) + 1));
//	ft_printf("%s\n", ptr_to_be_copied);
//}