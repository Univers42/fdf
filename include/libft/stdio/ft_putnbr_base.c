/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:35:36 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * a function that displays a number in a base given as a parameter.
 * The base is a string of all the characters that are used to represent
 * the numbers in the base. The function must be able to handle both
 * positive and negative numbers. If the base is invalid, the function
 * displays nothing. Here’s how it should be prototyped :
 * void ft_putnbr_base(int nbr, char *base);
 * @param int nbr
 * @param char* radix
 * @returns void
 * @note in a positional numeral system,
 * @note the radix or base is the number of unique digits,
 * @note including zero, used to represent numbers.
 * @note EXAMPLE: the radix of the decimal system is 10,
 * @note meaning it uses the digits 0-9 to represent numbers.
 * @note EXAMPLE: the radix of the binary system is 2,
 * @note meaning it uses the digits 0-1 to represent numbers.
 * @note EXAMPLE: the radix of the hexadecimal system is 16,
 * @note meaning it uses the digits 0-9 and the letters A-F to represent numbers.
 * @note EXAMPLE: the radix of the octal system is 8,
 * @note meaning it uses the digits 0-7 to represent numbers.
 * @note EXAMPLE: the radix of the sexagesimal system is 60,
 * @note meaning it uses the digits 0-9 and the letters A-Z to represent numbers.
 * @note EXAMPLE: the radix of the base64 system is 64,
 * @note meaning it uses the digits 0-9, 
 * @note the letters A-Z, and the symbols + and / to represent numbers.
 */
#include "../libft.h"

void	ft_putnbr_base(int nbr, char *radix)
{
	int		base;
	char	c;

	base = 0;
	while (radix[base])
		base++;
	if (base < 2 || base > 16)
		return ;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= base)
		ft_putnbr_base(nbr / base, radix);
	c = radix[nbr % base];
	write(1, &c, 1);
}
//
//int main(void)
//{
//	ft_printf("Testing ft_putnbr_base:\n");
//
//	ft_printf("Test 1: Decimal (Base 10)\nExpected: 12345\nOutput: ");
//	ft_putnbr_base(12345, "0123456789");
//	ft_printf("\n");
//
//	ft_printf("Test 2: Binary (Base 2)\nExpected: 11000000111001\nOutput: ");
//	ft_putnbr_base(12345, "01");
//	ft_printf("\n");
//
//	ft_printf("Test 3: Hexadecimal (Base 16)\nExpected: 3039\nOutput: ");
//	ft_putnbr_base(12345, "0123456789ABCDEF");
//	ft_printf("\n");
//
//	ft_printf("Test 4: Octal (Base 8)\nExpected: 30071\nOutput: ");
//	ft_putnbr_base(12345, "01234567");
//	ft_printf("\n");
//
//	ft_printf("Test 5: Negative Number (Base 10)\nExpected: -12345\nOutput: ");
//	ft_putnbr_base(-12345, "0123456789");
//	ft_printf("\n");
//
//	ft_printf("Test 6: Invalid Base (Base 1)\nExpected: \nOutput: ");
//	ft_putnbr_base(12345, "0");
//	ft_printf("\n");
//
//	ft_printf("Test 7: Invalid Base (Base 17)\nExpected: \nOutput: ");
//	ft_putnbr_base(12345, "0123456789ABCDEF0");
//	ft_printf("\n");
//
//	return 0;
//}