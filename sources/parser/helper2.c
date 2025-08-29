/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:50:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 18:48:10 by dlesieur         ###   ########.fr       */
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
 * @brief Parses a hexadecimal number from a string segment, handling
 * optional "0x" prefix.
 * 
 * This function attempts to convert a substring from `str` or `end`
 * into a 32-bit unsigned integer, supporting optional "0x" or "0X"
 * prefixes. it skips teh prefix if present, accumulates up to 8
 * hexadecinaml digits using `accumulate_hex`, and stores the result in
 * `*n`. If no valid digits are found. it returns 0. the function
 * returns the number of characters consumes from the start
 * @param n Pointer to a uint32_t where the parsed hexadecimal value
 * will be sorted
 * @param str Pointer to the start of teh string segment to parse
 * @param end Pointer to the end of the string  segment (non-inclusive)
 * @return The number of characters consumed; 0 if parsing fails
 * (no digits or invalid input)
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
