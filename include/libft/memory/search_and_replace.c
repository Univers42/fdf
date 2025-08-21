/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:02:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stdio/ft_stdio.h"
#include "../render/ft_stddef.h"

/**
 * This function iterates through the input string and prints each character.
 * If a character matches @to_find, it prints @to_replace instead.
 * Otherwise, it prints the original character.
 * The function uses only arithmetic and logical operations
 * The result is printed directly to standard output, followed by a newline.
 *
 * Example:
 *     ft_search_and_replace("banana", 'a', 'o');
 *     // Output: bonono
 */
void	ft_search_and_replace(char *str, char to_find, char to_replace)
{
	char	out;

	while (*str)
	{
		out = (*str == to_find) * to_replace + (*str != to_find) * (*str);
		ft_putchar_fd(out, STDOUT_FILENO);
		str++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

// Prototype for ft_search_and_replace
//int main(void)
//{
//    char str1[] = "hello world";
//    char str2[] = "banana";
//    char str3[] = "42 school";
//
//   	ft_printf("Original: %s\nReplace 'l' with 'x':\n", str1);
//    ft_search_and_replace(str1, 'l', 'x');
//
//   	ft_printf("Original: %s\nReplace 'a' with 'o':\n", str2);
//    ft_search_and_replace(str2, 'a', 'o');
//
//   	ft_printf("Original: %s\nReplace ' ' with '_':\n", str3);
//    ft_search_and_replace(str3, ' ', '_');
//
//    return 0;
//}