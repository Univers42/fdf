/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:50:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 14:46:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Verify the pattern of hexdigit encountered into the scope
int	hex_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

/**
 * This function while using all the pointert o update their current
 * positions will accumulate the value and digits
 * The purpose of this function is to parse up to 8 hexadecimal digits
 * from a character buffer (`curr` to `end`), accumulate
 * their value into `*acc` count how many digits were processed in *digits, 
 * and return the nu ber of characters consumed.
 * @param acc pointer to acc
 * @param cur pointer to current character
 * @param end pointer to end character to end of chunk
 * @param digits pointer to digits
 * @return number of consumed characters; updates *acc and *digits
 * it reads each character, checks if it's a valid hex digit.
 * if valid, it shifts the accumulator left by 4 bits and adds the digit value
 * stops after 8 digits or an invalid character
 * update both the accumulator and digit count via pointers
 * return how many characters were processed
 */
int	accumulate_hex(uint32_t *acc, char *cur, char *end, int *digits)
{
	int	val;
	int	len;

	len = 0;
	*digits = 0;
	while (cur < end)
	{
		val = hex_digit(*cur);
		if (val < 0 || *digits == 8)
			break ;
		*acc = (*acc << 4) | (uint32_t)val;
		++(*digits);
		++cur;
		++len;
	}
	return (len);
}

/**
 * @param n
 * @param str
 * @param end
 * 
 */
int	strntohex(uint32_t *n, char *str, char *end)
{
	uint32_t	acc;
	int			digits;
	char		*cur;

	cur = str;
	if (cur >= end)
		return (0);
	(void)skip_prefix(&cur, end);
	acc = 0;
	digits = 0;
	cur += accumulate_hex(&acc, cur, end, &digits);
	if (digits == 0)
		return (0);
	*n = acc;
	return ((int)(cur - str));
}
