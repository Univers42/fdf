/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:05:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../ctype/ft_ctype.h"
#include "../stdio/ft_stdio.h"

int	ft_countwords(const char *s1, const char limiter)
{
	int	count;
	int	in_word;

	if (!s1)
		return (0);
	count = 0;
	in_word = 0;
	while (*s1)
	{
		if (*s1 != limiter && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s1 == limiter)
			in_word = 0;
		s1++;
	}
	return (count);
}

int	ft_countwords_space(const char *s1)
{
	return (ft_countwords(s1, ' '));
}

//int main(int argc, char **argv)
//{
//    const char *str;
//    if (argc != 2)
//        return (write(1,"\n",1), 1);
//    str = argv[1];
//   	ft_printf("%d\n", ft_countwords(str));
//    return (0);
//}