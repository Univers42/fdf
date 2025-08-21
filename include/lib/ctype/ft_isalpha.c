/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:40:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "TDD/test.h"
/**
 * Checks if the given character is an alphabetic letter.
 * An alphabetic character is either an uppercase letter (A-Z) 
 * or a lowercase letter (a-z).
 * 
 * @param c The character to check (represented as an int, 
 * typically from an unsigned char or EOF).
 * @return 1 if the character is alphabetic, 0 otherwise.
 * c | 32 ensure the 6th bit is set effectively converting uppercase to lower
 */
int	ft_isalpha(int c)
{
	return ((unsigned)((c | 32) - 'a') < 26);
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
//        int std = isalpha(c);
//        int mine = ft_isalpha(c);
//        
//        // Compare truthiness (not the exact values)
//        if ((!!std) != (!!mine))
//        {
//           	ft_printf("Mismatch for c = %d ('%c'): "
//            "isalpha = %d, ft_isalpha = %d\n",
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