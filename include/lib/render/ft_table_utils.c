/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:35:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"
#include "ft_stdio.h"

static void	print_border_char(char *corner)
{
	if (strcmp(corner, "┌") == 0)
		ft_printf("┐\n");
	else if (strcmp(corner, "├") == 0)
		ft_printf("┤\n");
	else
		ft_printf("┘\n");
}

static void	print_separator_char(char *corner)
{
	if (strcmp(corner, "┌") == 0)
		ft_printf("┬");
	else if (strcmp(corner, "├") == 0)
		ft_printf("┼");
	else
		ft_printf("┴");
}

void	print_table_border(int cols, char *corner, char *line)
{
	int	i;
	int	j;

	ft_printf("%s", corner);
	i = 0;
	while (i < cols)
	{
		j = 0;
		while (j < 14)
		{
			ft_printf("%s", line);
			j++;
		}
		if (i < cols - 1)
			print_separator_char(corner);
		i++;
	}
	print_border_char(corner);
}
