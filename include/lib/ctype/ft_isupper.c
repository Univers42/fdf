/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:28:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/**
 * Checks if the given character is an uppercase letter.
 * 
 * @param c The character to check (represented as an int)
 * @return 1 if the character is uppercase, 0 otherwise.
 */
int	ft_isupper(int c)
{
	unsigned int	not_below_a;
	unsigned int	not_above_z;

	not_below_a = !((c - 'A') >> 31);
	not_above_z = !(('Z' - c) >> 31);
	return ((not_below_a & not_above_z) << 8);
}
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#include <stdio.h>
//#include <ctype.h>
//#include "ft_ctype.h"
//
//// ...existing code...
//int main(void)
//{
//    int errors = 0;
//    for (int c = 0; c < 128; ++c)
//    {
//        int std = isupper(c);
//        int mine = ft_isupper(c);
//        if ((!!std) != (!!mine))
//        {
// 	ft_printf("Mismatch for c = %d ('%c'): isupper = %d, ft_isupper = %d\n",
//                   c, (c >= 32 && c < 127) ? c : '.', std, mine);
//            errors++;
//        }
//    }
//    if (errors == 0)
//       	ft_printf("All tests passed!\n");
//    else
//       	ft_printf("%d mismatches found.\n", errors);
//    return errors;
//}
//// ...existing code...