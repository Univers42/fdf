/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:26:21 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return ((c ^ ' ') == 0 || (c ^ '\t') == 0
		|| (c ^ '\n') == 0 || (c ^ '\r') == 0
		|| (c ^ '\v') == 0 || (c ^ '\f') == 0);
}
//
//#include <stdio.h>
//#include <ctype.h>
//
//int main(void)
//{
//    int errors = 0;
//    
//    for (int c = 0; c < 128; ++c)
//    {
//        int std = isspace(c);
//        int mine = ft_isspace(c);
//        
//        // Compare truthiness (not the exact values)
//        if ((!!std) != (!!mine))
//        {
//     	ft_printf("Mismatch for c = %d ('%c'): isspace = %d, ft_isspace = %d\n",
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