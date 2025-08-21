/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:45:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/04 14:28:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDER_H
# define FT_RENDER_H

# include "ft_stddef.h"
# include "ft_colors.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <string.h>

/* Banner styles */
typedef enum e_banner_style
{
	BANNER_SIMPLE,
	BANNER_DOUBLE,
	BANNER_ROUNDED
}	t_banner_style;

typedef struct s_graph_params
{
	int	max_val;
	int	max_height;
	int	row;
}	t_graph_params;

/* Core rendering functions */
void	ft_print_banner(const char *title, const char *subtitle,
			t_banner_style style);
void	ft_print_boxed(const char *text);
void	ft_clear_screen(void);
void	ft_move_cursor(int x, int y);
void	ft_print_centered(const char *text);

/* Advanced rendering functions */
void	ft_print_table(char **headers, char ***data, int rows, int cols);
void	ft_print_loading_spinner(int duration_ms);
void	ft_print_notification(const char *title, const char *message,
			const char *type);
void	ft_print_code_block(const char *code, const char *language);
void	ft_print_diff(const char *old_line, const char *new_line);
void	ft_print_emoji_status(const char *message, const char *emoji);

/* Animation and interactive functions */
void	ft_typewriter_effect(const char *text, int delay_ms);
void	ft_print_menu(char **options, int count, int selected);
void	ft_print_timeline(char **events, char **times, int count);
void	ft_print_graph(int *values, int count, int max_height);

/* Table utility functions */
void	print_table_border(int cols, char *corner, char *line);

/* Utility functions */
int		ft_get_terminal_width(void);
int		ft_get_terminal_height(void);

#endif
