/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:48:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/29 17:14:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "./TDD/test.h"
/**
 * Writes the character `c` to the given file descriptor `fd`.
 * 
 * @param c The character to write.
 * @param fd The file descriptor to write to.
 * 
 * @return Nothing.
 * 
 * @note This function uses the system call `write` to output the character `c`
 *       to the specified file descriptor, which could be standard output (1), 
 *       standard error (2), or any other file descriptor.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
//int main(void)
//{
//	test_putchar_fd();
//	return 0;
//}