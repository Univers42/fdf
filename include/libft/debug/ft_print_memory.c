/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:43:35 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/ft_stddef.h"
#include "../stdio/ft_stdio.h"
#include "ft_debug.h"
#include <stdio.h>
/**
 * Prints the memory content of a given address.
 * @param addr The address to print
 * @param size The size of the memory to print
 * @return The address of the memory
 * @note This function prints the memory content of a given address
 * @note in a hexadecimal format.
 * @note EXAMPLE: ft_print_memory("Hello, World!", 13) prints:
 * @note 48 65 6c 6c 6f 2c 20 57 6f 72 6c 64 21
 * @note EXAMPLE: ft_print_memory("Hello, World!", 5) prints:
 * @note 48 65 6c 6c 6f
 * @note EXAMPLE: ft_print_memory("Hello, World!", 0) prints:
 */
void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;
	unsigned char	*p;
	unsigned int	chunk_size;

	p = (unsigned char *)addr;
	i = 0;
	while (i < size)
	{
		if (size - i > 16)
			chunk_size = 16;
		else
			chunk_size = size - i;
		ft_print_hex(p + i, chunk_size, (unsigned long)(p + i));
		ft_print_ascii(p + i, chunk_size);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i += 16;
	}
	return (addr);
}

//#include <stdio.h>
//#include "../libft.h"
//
//int main(void)
//{
//    char buffer[] = "Hello, World!\nThis is
// a test buffer for ft_print_memory.\x01\x7F";
//    unsigned int size = sizeof(buffer) - 1; // exclude null terminator
//
//   	ft_printf("Memory dump:\n");
//    ft_print_memory(buffer, size);
//
//    return 0;
//}