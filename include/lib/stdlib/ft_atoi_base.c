/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:09:31 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/09 19:53:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_stddef.h"
#include "limits.h"

/**
 * write a function that converts the initial portion 
 * of the string pointed to by nptr to int representation.
 * @param char* str the string to convert
 * @param char* base the radix of the number
 * @returns int
 * @note The expected input is a string of characters 
 * that represent a number in the given base.
 * @note The expected output is the integer representation of the number.
 * @note EXAMPLE: ft_atoi("12345", "0123456789") returns 12345
 * @note EXAMPLE: ft_atoi("1010", "01") returns 10
 * @note EXAMPLE: ft_atoi("A", "0123456789ABCDEF") returns 10
 * @note EXAMPLE: ft_atoi("A", "01") returns 0
 * @note EXAMPLE: ft_atoi("A", "0123456789") returns 0
 * @note EXAMPLE: ft_atoi("A", "0123456789ABCDEF") returns 10
 * @note EXAMPLE: ft_atoi("A", "0123456789ABCDEF") returns 10
 */

/* Check if the digit is valid for the given base */
static int	is_valid_for_base(int digit, int base)
{
	return (digit < base);
}

static int	conv_char(char c)
{
	int	digit;
	int	upper_case;
	int	lower_case;

	digit = 0;
	if (c >= '0' && c <= '9')
		digit = c - '0';
	upper_case = 0;
	if (c >= 'A' && c <= 'Z')
		upper_case = c - 'A' + 10;
	lower_case = 0;
	if (c >= 'a' && c <= 'z')
		lower_case = c - 'a' + 10;
	return (digit | upper_case | lower_case);
}

/* Process digits and accumulate result */
static int	process_digits(const char *str, int base, int sign)
{
	int	res;
	int	digit;
	int	valid;

	res = 0;
	while (*str)
	{
		digit = conv_char(*str);
		valid = is_valid_for_base(digit, base);
		if (!valid)
			break ;
		if (res > (INT_MAX - digit) / base)
		{
			if (sign == 1)
				return (INT_MAX);
			return (INT_MIN);
		}
		res = res * base + digit;
		str++;
	}
	return (res * sign);
}

/* Convert string to integer in specified base */
int	ft_atoi_base(const char *str, int base)
{
	int	sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '+' || *str == '-')
		return (0);
	return (process_digits(str, base, sign));
}

//int main(int argc, char *argv[])
//{
//    int base;
//    char *endptr, *str;
//    long val;
//    int val_atoi;
//    
//    if (argc < 2)
//    {
//        fprintf(stderr, "Usage: %s str [base]\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }
//    str = argv[1];
//    base = (argc > 2) ? atoi(argv[2]) : 0;
//    errno = 0;
//    strtol("0", NULL, base);
//    if (errno == EINVAL)
//    {
//        perror("strtol");
//        exit(EXIT_FAILURE);
//    }
//    errno = 0;
//    val = strtol(str, &endptr, base);
//    val_atoi = ft_atoi_base(str, base);
//    if (errno == ERANGE)
//    {
//        perror("strtol");
//        exit(EXIT_FAILURE);
//    }
//    //if (endptr == str)
//    //{
//    //    fprintf(stderr, "No digits were found\n");
//    //    exit(EXIT_FAILURE);
//    //}
//
//   	ft_printf("strtol() returned %ld\n", val);
//   	ft_printf("ft_atoi_base() returned %d \n", val_atoi);
//    if (*endptr != '\0')
//       	ft_printf("Further characters after number: \"%s\"\n", endptr);
//    exit(EXIT_SUCCESS);
//}
////int main()
//{
//   	ft_printf("%d\n", ft_atoi_base("101010", 2));       // Binary: 42
//   	ft_printf("%d\n", ft_atoi_base("2A", 16));         // Hexadecimal: 42
//   	ft_printf("%d\n", ft_atoi_base("--42", 10));       // Decimal: 42
//   	ft_printf("%d\n", ft_atoi_base("  +42", 10));      // Decimal: 42
//   	ft_printf("%d\n", ft_atoi_base("Z", 36));          // Base 36: 35
//   	ft_printf("%d\n", ft_atoi_base("++42", 10));       // Decimal: 42
//   	ft_printf("%d\n", ft_atoi_base("-+42", 10));       // Decimal: -42
//   	ft_printf("%d\n", ft_atoi_base("+-42", 10));       // Decimal: -42
//   	ft_printf("%d\n", ft_atoi_base("--42", 10));       // Decimal: 42
//   	ft_printf("%d\n", ft_atoi_base("0", 10));          // Decimal: 0
//   	ft_printf("%d\n", ft_atoi_base("123abc", 20));     // Base 20: 1784780
//    return 0;
//}