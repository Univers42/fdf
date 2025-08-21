/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:52:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if the given character is a blank character.
 * In the "C" locale, blank characters are: space (' ')
 * 
 * @param c The character to check (represented as an int)
 * @return 1 if the character is blank, 0 otherwise.
 */
int	ft_isblank(int c)
{
	return (((c ^ ' ') == 0) || ((c ^ '\t') == 0));
}
//
//#include <stdio.h>
//#include <ctype.h>
//
//int main(void)
//{
//    int errors = 0;
//    
//    for (int c = -10; c < 128; ++c)
//    {
//        int std = isblank(c);
//        int mine = ft_isblank(c);
//        
//        // Compare truthiness (not the exact values)
//        if ((!!std) != (!!mine))
//        {
//       	ft_printf("Mismatch for c = %d ('%c'): isblank = %d,
// ft_isblank = %d\n",
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