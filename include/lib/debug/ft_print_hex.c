/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:47:24 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../stdio/ft_stdio.h"

void	ft_print_hex(unsigned char *p, unsigned int size, unsigned long addr)
{
	unsigned int	j;
	char			*hex;

	hex = "0123456789abcdef";
	ft_putnbr_base(addr, "0123456789abcdef");
	ft_putstr_fd(": ", STDOUT_FILENO);
	j = 0;
	while (j < 16 && j < size)
	{
		ft_putchar_fd(hex[p[j] / 16], STDOUT_FILENO);
		ft_putchar_fd(hex[p[j] % 16], STDOUT_FILENO);
		if (j % 2 == 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		j++;
	}
	while (j < 16)
	{
		ft_putstr_fd("  ", STDOUT_FILENO);
		if (j % 2 == 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		j++;
	}
}

//#include <stdio.h>
//#include <unistd.h>
//#include "../libft.h"
//
//int main(void)
//{
//    unsigned char buffer[20] = {
//        'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 
//'d', '!', 0x0A, 0x00, 0x7F, 0x20, 0x41, 0x42, 0x43
//    };
//
//   	ft_printf("Hex output:\n");
//    ft_print_hex(buffer, 20, (unsigned long)buffer);
//   	ft_printf("\n");
//
//    return 0;
//}