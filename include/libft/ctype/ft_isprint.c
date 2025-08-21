/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:08:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/**
 * Checks if the given character is printable, including space.
 * Printable characters are those with values between 32 
 * and 126 (inclusive) in the ASCII table.
 * 
 * @param c The character to check (represented as an int, 
 * typically from an unsigned char or EOF).
 * @return 1 if the character is printable, 0 otherwise.
 * The expression (c - 32) | (126 - c) will result in a negative 
 * number (with the high bit set) if either c < 32 or c > 126
Shifting right by 31 isolates this sign bit (1 if out of range, 0 if in range)
XORing with 1 inverts this (1 if in range, 0 if out of range)
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
//
//#include <stdio.h>
//#include <ctype.h>
//
//
//int main(void)
//{
//    int errors = 0;
//    
//    for (int c = 0; c < 128; ++c)
//    {
//        int std = isprint(c);
//        int mine = ft_isprint(c);
//        
//        // Compare truthiness (not the exact values)
//        if ((!!std) != (!!mine))
//        {
//    	ft_printf("Mismatch for c = %d ('%c'): isprint = %d, ft_isprint = %d\n",
//                   c, (c >= 32 && c < 127) ? c : '.', std, mine);
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