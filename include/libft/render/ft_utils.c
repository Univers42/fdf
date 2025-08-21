/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:35:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"
#include "ft_stdio.h"

void	ft_clear_screen(void)
{
	ft_printf("\033[2J\033[H");
	fflush(stdout);
}

void	ft_move_cursor(int x, int y)
{
	ft_printf("\033[%d;%dH", y, x);
	fflush(stdout);
}

int	ft_get_terminal_width(void)
{
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
		return (w.ws_col);
	return (80);
}

int	ft_get_terminal_height(void)
{
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
		return (w.ws_row);
	return (24);
}

void	ft_print_centered(const char *text)
{
	int	width;
	int	padding;
	int	i;

	if (!text)
		return ;
	width = ft_get_terminal_width();
	padding = (width - (int)strlen(text)) / 2;
	i = 0;
	while (i < padding)
	{
		ft_printf(" ");
		i++;
	}
	ft_printf("%s\n", text);
}
