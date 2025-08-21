/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:37:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/29 17:15:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include <unistd.h>

void	ft_first_word(char *str)
{
	int		count;
	char	*temp;

	count = 0;
	while (ft_isspace(*str))
		str++;
	temp = str;
	while (!ft_isspace(*str))
	{
		count++;
		str++;
	}
	write(1, temp, count);
	write(1, "\n", 1);
}

/*
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	char *str = argv[1];
	ft_first_word(str);
	return (0);
}
 */