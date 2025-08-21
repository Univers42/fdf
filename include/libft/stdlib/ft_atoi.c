/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:23:59 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_limits.h"
#include "ft_ctype.h"
#include <stddef.h>
#include <limits.h>

/**
 * Convert a nptring to an integer
 * @param nptr The input nptring
 * @return The converted integer
 * @note This function skips leading whitespaces, 
 * handles an optional sign, and converts the numerical 
 * characters to an integer.
 */
int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (sign == 1 && result > (LONG_MAX - digit) / 10)
			return (INT_MAX);
		if (sign == -1 && (-result) < (LONG_MIN + digit) / 10)
			return (INT_MIN);
		result = (result * 10) + digit;
		str++;
	}
	return ((int)(result * sign));
}
/**
 * Scenario: command line argument parsing
 * iamgine you're building a command-line tool
 * that processes numerical input. 
 * One of the common tasks in such program is 
 * reading integers from the command line
 * and converting them from strings to actual 
 * members so that they can be used 
 * in calculations or logic.
 */
//int main(int argc, char **argv)
//{
//	if(argc != 4)
//	{
//		ft_printf("./usage [param1]..[param4] *numbers_only");
//		return  1;
//	}
//	
//	int num1 = ft_atoi(argv[1]);
//	int num2 = ft_atoi(argv[3]);
//	char operator = argv[2][0];
//
//	if(	ft_strncmp(argv[2], "+",1) != 0
//	 	&& ft_strncmp(argv[2], "-",2) != 0 
//		&& ft_strncmp(argv[2], "*",2) != 0
//		&& ft_strncmp(argv[2], "/",2) != 0
//		)
//		{
//			ft_printf("Err: Invalid operator. Use one of:"
//			"+, -, *, /\n");
//			return 2;
//		}
//	switch (operator)
//    {
//    case '+':
//       	ft_printf("Result: %d\n", num1 + num2);
//        break;
//    case '-':
//       	ft_printf("Result: %d\n", num1 - num2);
//        break;
//    case '*':
//       	ft_printf("Result: %d\n", num1 * num2);
//        break;
//    case '/':
//        if (num2 == 0)
//        {
//           	ft_printf("Error: Division by zero is not allowed.\n");
//            return 1;
//        }
//       	ft_printf("Result: %d\n", num1 / num2);
//        break;
//    default:
//       	ft_printf("Error: Invalid operator. Use one of:"
//			" +, -, *, /\n");
//        return 1;
//    }
//	return 0;
//}