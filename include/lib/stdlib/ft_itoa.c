/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:11:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stddef.h"
#include <stdlib.h>

static int	ft_len(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		++count;
	while (n)
	{
		++count;
		n /= 10;
	}
	return (count);
}

/**
 * Converts an integer to a null-terminated string using decimal representation.
 * 
 * @param n The integer to convert.
 * @return A pointer to the newly allocated string representing the integer, 
 *         or NULL if memory allocation fails.
 * 
 * @note The returned string must be freed by the caller to avoid memory leaks.
 */
char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;

	len = ft_len(n);
	ptr = malloc(len + 1);
	if (NULL == ptr)
		return (NULL);
	*(ptr + len) = '\0';
	if (n == 0)
		*ptr = '0';
	else if (n < 0)
		*ptr = '-';
	while (n)
	{
		if (n < 0)
			*(ptr + --len) = (~(n % 10) + 1) + 48;
		else
			*(ptr + --len) = (n % 10) + 48;
		n /= 10;
	}
	return (ptr);
}
/**
 * here we're going to tacle a real problem
 * wbe used in embedded system or low-level programming
 * Where we might need to display some integers
 * We're going to build a simple temperature monitoring
 * system on a microcontroller that reads data from a
 * temperature and logs it
 */

//char *ft_itoa_base(int value, int base) {
//    static char *digits = "0123456789ABCDEF";
//    char *buffer;
//    char *start;
//    int length;
//
//	buffer = malloc(ft_log10(value));
//	if(!buffer)
//		return NULL;
//	digits = "0123456789ABCDEF";
//    if (value == 0) {
//		ft_calloc(2, sizeof(char));
//		ft_memcpy(0, buffer, 1);
//		ft_memcpy(0, buffer, 1);
//        return buffer;
//    }
//    length = 1;
//    int temp = value;
//    while (temp /= base)
//        length++;
//
//    buffer = malloc(length + 1);
//    if (!buffer)
//        return NULL;
//    start = buffer + length;
//    *start = '\0';
//    while (value) {
//        *(--start) = digits[value % base];
//        value /= base;
//    }
//    return buffer;
//}
//
//void log_hash_as_hex(int hash_value)
//{
//	char *hex_str;
//    hex_str = ft_itoa_base(hash_value, 16);
//   	ft_printf("Hash value: %s\n", hex_str);
//}
//
//int main(void) {
//    int hash_value = 439384457;
//    log_hash_as_hex(hash_value);
//    return 0;
//}
