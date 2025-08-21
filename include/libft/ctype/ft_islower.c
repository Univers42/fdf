/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/**
 * Checks if the given character is a lowercase letter.
 * 
 * @param c The character to check (represented as an int, 
 * typically from an unsigned char or EOF).
 * @return 1 if the character is lowercase, 0 otherwise.
 */
int	ft_islower(int c)
{
	return ((unsigned)(c - 'a') < 26);
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
//        int std = islower(c);
//        int mine = ft_islower(c);
//        
//        // Compare truthiness (not the exact values)
//        if ((!!std) != (!!mine))
//        {
//   	ft_printf("Mismatch for c = %d ('%c'): islower = %d, ft_islower = %d\n",
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