/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:51:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"
#include "../stdio/ft_stdio.h"
#include "../render/ft_stddef.h"
#include "../stdlib/ft_stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "../ctype/ft_ctype.h"

void	*ft_print_array(int *arr, int size, char mode)
{
	int	i;

	if (!arr || size <= 0)
		return (arr);
	i = 0;
	if (mode == 'v')
	{
		while (i < size)
		{
			ft_printf("[%i] --> %i \n", i, arr[i]);
			i++;
		}
		return (arr);
	}
	while (i < size)
	{
		ft_putnbr_fd(arr[i], STDOUT_FILENO);
		if (i < size - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (arr);
}

void	print_array(int *arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		ft_printf("%d ", arr[i]);
	ft_printf("\n");
}

//int main(int argc, char **argv)
//{
//    int *arr;
//    int size;
//    int i;
//    char mode = 'h'; // default horizontal mode
//    int start_index = 1; // where numbers start in argv
//
//    if (argc < 2)
//        return (ft_putchar_fd('\n', STDOUT_FILENO), 1);
//    
//    // Check if first argument is a mode flag or a number
//    if (argc > 2 && argv[1][0] && !ft_isdigit(argv[1][0]) 
//&& argv[1][0] != '-' && argv[1][0] != '+')
//    {
//        // First argument is a mode flag
//        mode = argv[1][0];
//        start_index = 2;
//        size = argc - 2;
//    }
//    else
//    {
//        // First argument is a number, use default mode
//        mode = 'h'; // horizontal mode
//        start_index = 1;
//        size = argc - 1;
//    }
//    
//    if (size <= 0)
//        return (ft_putchar_fd('\n', STDOUT_FILENO), 1);
//    
//    arr = calloc(size, sizeof(int));
//    if (!arr)
//        return (1);
//    
//    i = 0;
//    while (i < size)
//    {
//        arr[i] = atoi(argv[start_index + i]);
//        i++;
//    }
//    
//    ft_print_array(arr, size, mode);
//    free(arr);
//    return (0);
//}