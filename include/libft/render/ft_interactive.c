/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:00:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"
#include "../stdio/ft_stdio.h"
#include "ft_colors.h"

void	ft_print_menu(char **options, int count, int selected)
{
	int	i;

	i = 0;
	ft_printf("\n%s┌─ SELECT OPTION ─┐%s\n", CYAN_TERM, RESET_TERM);
	while (i < count)
	{
		if (i == selected)
			ft_printf("%s│ ► %-12s │%s\n", GREEN_TERM, options[i], RESET_TERM);
		else
			ft_printf("%s│   %-12s │%s\n", WHITE_TERM, options[i], RESET_TERM);
		i++;
	}
	ft_printf("%s└─────────────────┘%s\n", CYAN_TERM, RESET_TERM);
}

static void	print_timeline_item(char *time, char *event, int is_last)
{
	if (is_last)
		ft_printf("%s└─ %s%s %s%s\n", CYAN_TERM, time, RESET_TERM, event,
			RESET_TERM);
	else
	{
		ft_printf("%s├─ %s%s %s%s\n", CYAN_TERM, time, RESET_TERM, event,
			RESET_TERM);
		ft_printf("%s│%s\n", CYAN_TERM, RESET_TERM);
	}
}

void	ft_print_timeline(char **events, char **times, int count)
{
	int	i;

	i = 0;
	ft_printf("\n%s── TIMELINE ──%s\n", CYAN_TERM, RESET_TERM);
	while (i < count)
	{
		print_timeline_item(times[i], events[i], (i == count - 1));
		i++;
	}
}

static void	print_graph_row(int *values, int count, t_graph_params params)
{
	int	i;
	int	bar_height;

	i = 0;
	while (i < count)
	{
		bar_height = (values[i] * params.max_height) / params.max_val;
		if (bar_height >= params.row)
			ft_printf("%s█%s", GREEN_TERM, RESET_TERM);
		else
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
}

void	ft_print_graph(int *values, int count, int max_height)
{
	t_graph_params	params;
	int				i;

	params.max_val = 0;
	i = 0;
	while (i < count && values[i] > params.max_val)
		params.max_val = values[i++];
	params.row = max_height;
	while (params.row > 0)
	{
		print_graph_row(values, count, params);
		params.row--;
	}
	i = 0;
	while (i < count)
	{
		ft_printf("%d", values[i] % 10);
		i++;
	}
	ft_printf("\n");
}
