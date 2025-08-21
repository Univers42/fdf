/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:05:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:52:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/**
 * Checks if the given character is part of the ASCII character set.
 * The ASCII character set includes characters with values from 0 to 127.
 * `~0x7F` is a bitwise NOT operation that clears the first 7 bits of c.
 * `(c & ~ 0x7F)` will be non-zero if c is outside the ASCII range.
 * !((c & ~0x7F)) will be 1 if c is in the ASCII range (0-127).
 * @param c The character to check (represented as an int, 
 * typically from an unsigned char or EOF).
 * @return 1 if the character is in the ASCII range, 0 otherwise.
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
//
//#include <stdio.h>
//#include <ctype.h>
//
//int main(void)
//{
//    int errors = 0;
//    for (int c = -10; c < 150; ++c)
//    {
//        int std = isascii(c);
//        int mine = ft_isascii(c);
//        
//        // Compare truthiness (not the exact values)
//        if ((!!std) != (!!mine))
//        {
//           	ft_printf("Mismatch for c = %d: isascii = %d,
// ft_isascii = %d\n",
//                   c, std, mine);
//            errors++;
//        }
//    }
//    
//    if (errors == 0)
//       	ft_printf("All tests passed!\n");
//    else
//       	ft_printf("%d mismatches found.\n", errors);
//        
//    return errors;
//}