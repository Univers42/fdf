/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:14:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/29 17:14:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "TDD/test.h"
/**
 * Writes the string `s` to the given file descriptor `fd`.
 * 
 * @param s The string to write.
 * @param fd The file descriptor to write to.
 * @return The number of characters written.
 * 
 * @note 
 * If the string `s` is NULL, the function does nothing. 
 * The function will write the string character 
 * by character to the specified file descriptor.
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

//int main(void)
//{
//	test_putstr_fd();
//	return 0;
//}