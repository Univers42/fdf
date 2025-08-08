/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntoi.c                                       :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libft/libft.h"

#define CUTOFF 214748364
#define HEXTABLE "0123456789abcdef"

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

static inline bool	skip_prefix(char **str, char *end)
{
	if (*str + 1 < end && **str == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
	{
		*str += 2;
		return (true);
	}
	return (false);
}

int	strntohex(uint32_t *n, char *str, char *end)
{
	uint32_t	acc;
	int			digits;
	char		c;
	char		*cur;
	bool		has_prefix;

	cur = str;
	if (cur >= end)
		return (0);
	has_prefix = skip_prefix(&cur, end);
	acc = 0;
	digits = 0;
	while (cur < end)
	{
		c = *cur;
		if (c >= '0' && c <= '9')
			c = c - '0';
		else if (c >= 'a' && c <= 'f')
			c = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			c = c - 'A' + 10;
		else
			break ;
		if (digits == 8) // limit (prevent overflow & absurd long color)
			break ;
		acc = (acc << 4) | (uint32_t)c;
		++digits;
		++cur;
	}
	// require at least one digit; if prefix present, still same rule
	if (digits == 0)
		return (0);
	// optional: if prefix present we already advanced; variable used for logic (can extend later)
	if (has_prefix && digits == 0)
		return (0);
	*n = acc;
	return (int)(cur - str); // includes prefix length if present
}
