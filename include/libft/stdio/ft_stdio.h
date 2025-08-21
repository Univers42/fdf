/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:30:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:54:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

# include "ft_stddef.h"
# include "get_next_line.h"

typedef int	(*t_ops)(int, int);

char	*get_next_line(int fd);
void	ft_first_word(char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_base(int nbr, char *radix);
int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *format, ...);
int		ft_printf(const char *format, ...);
#endif