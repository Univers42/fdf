/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:47:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 18:43:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libft.h"
#include "fdf.h"

#define CUTOFF 214748364
#define HEXTABLE "0123456789abcdef"

/**
 * @brief Parses an FDF file by reading and processing its contents.
 * 
 * This function opens the specified file in read-only mode, allocates
 * a buffer for parsing, initialize a parser structure, and delegates
 * the actual parsing to parse_buffered.
 * it handles file opening errors by printing an error message,
 * ensures proper cleanup of resources (closing file descriptor
 * and freeing buffer), and return the success status.
 * @param fdf pointer to the app structure where parsed data will be stored
 * @param filename The path to the fdf file to be parsed
 * @return true if the file is parsed succcessfully; false if an error occurs
 * (file not found or parsing failure)
 */
bool	parse_file(t_app *fdf, char *filename)
{
	bool		ok;
	t_parser	parser;
	int			fd;

	ok = false;
	parser = (t_parser){0};
	parser.buf = malloc(INPUT_BUF_SIZE);
	fd = open(filename, O_RDONLY);
	if (fd >= 0)
	{
		if (parser.buf != NULL)
			ok = parse_buffered(&parser, fdf, fd);
		close(fd);
	}
	else
		perror("open: ");
	free(parser.buf);
	return (ok);
}

/**
 * @brief Checks for and consumes an optional sign character in the string
 * 
 * This function examines the character at the current index in the 
 * string. if it is a '+' or '-', it determines if the sign is negative,
 * advances the idnex to teh next character, and returs the sign status.
 * if no sign is presnt or the index is out of bounds. it returns false(positive)
 * 
 * @param str the input string being parsed.
 * @param i Pointer to the current index in the string: incremented if a sign
 * is consumed
 * @param max The maximum value valid index in the string
 * @return true if a negative sign '-' is foudn and consumed:
 * false otherwise
 */
static inline bool	negative(const char *str, size_t *i, size_t max)
{
	bool	is_negative;

	is_negative = false;
	if (*i <= max && (str[*i] == '+' || str[*i] == '-'))
	{
		is_negative = str[*i] == '-';
		++*i;
	}
	return (is_negative);
}

/**
 * @brief Parses an integer from a string with a max length
 * handling signs and overflow.
 * This function attempts to convert a substring of the input
 * string to an integer, starting from the beginning, up to a specified
 * maximum length. it handles optional leading `+` or `-` signs,
 * accumulates digits while checking for integer overflow using predefined
 * cutoffs (CUTOFF == 214748364)
 * If the number would overflow accumulation stops. The result is stored in
 * *n, negated if  negative.
 * @param n Pointer to an integer where the parse value will be stored
 * @param str the input string to parse
 * @param max	The maximum number of characters to consider from the string.
 * @return	the number of characters successfully parsed (including sign if
 * present); 0 is parsing fails.
 */
int	ft_strntoi(int *n, char *str, size_t max)
{
	size_t			i;
	bool			is_negative;
	unsigned int	nlim;
	unsigned int	accumulator;

	i = 0;
	is_negative = negative(str, &i, max);
	nlim = 7;
	if (is_negative)
		nlim = 8;
	if (!ft_isdigit(str[i]))
		return (0);
	accumulator = 0;
	while (i <= max && ft_isdigit(str[i]))
	{
		if (accumulator > CUTOFF || (accumulator == CUTOFF
				&& (unsigned int)(str[i] - '0') > nlim))
			break ;
		accumulator = accumulator * 10 + (str[i] - '0');
		++i;
	}
	*n = (int)accumulator;
	if (is_negative)
		*n = (int)-accumulator;
	return ((int)i);
}

/**
 * @brief Skips the hexadecimal prefix "0x" or "0X" from
 * the string pointer
 * 
 * This function checks if the current position in the string
 * starts with "0x" or "0X"
 * if so, it advances the string pointer by 2 characters to skip
 * the prefix and returns true.
 * @param str Pointer to pointer  to the curr pos updated if prexi is skipped
 * @param end Pointer to the end of string buffer
 * @return true if the hexadecimal prefix was found and skipped; false otherwise
 */
bool	skip_prefix(char **str, char *end)
{
	if (*str + 1 < end && **str == '0' && ((*str)[1] == 'x'
		|| (*str)[1] == 'X'))
	{
		*str += 2;
		return (true);
	}
	return (false);
}
