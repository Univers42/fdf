/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isgraph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/**
 * Checks if the given character has a graphical representation.
 * Graphical characters are those with values between 33 (!) and 126 (~)
 * inclusive in the ASCII table - all printable characters except space.
 * 
 * @param c The character to check (represented as an int)
 * @return 1 if the character is graphical, 0 otherwise.
 */
int	ft_isgraph(int c)
{
	return (!(((c - 33) | (126 - c)) >> 31));
}
//
//#include <stdio.h>
//#include <ctype.h>
//
//int main(void)
//{
//    int errors = 0;
//    
//    for (int c = -10; c < 150; ++c)
//    {
//        int std = isgraph(c);
//        int mine = ft_isgraph(c);
//        
//        // Compare truthiness (not the exact values)
//        if ((!!std) != (!!mine))
//        {
//    	ft_printf("Mismatch for c = %d ('%c'): isgraph = %d, ft_isgraph = %d\n",
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