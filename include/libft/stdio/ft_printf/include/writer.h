/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:47:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:52:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITER_H
# define WRITER_H

# include <stddef.h>
# include <stdbool.h>

# define BUF_SIZE 2048

typedef struct s_writer
{
	size_t			index;	
	unsigned char	buf[BUF_SIZE];
	int				error;
	int				n_written;
	int				fd;
}	t_writer;

bool	writer_write(t_writer *w, const char *mem, size_t size);
bool	writer_write_str(t_writer *w, const char *str);
int		writer_flush(t_writer *w);
bool	writer_is_full(t_writer *w);
bool	writer_putchar(t_writer *w, char c);
void	writer_reset(t_writer *w);
bool	writer_pad_with(t_writer *w, char c, size_t n);
void	writer_write_hex(t_writer *w, size_t n, size_t len, bool upper);
void	writer_write_uint(t_writer *w, unsigned int n, size_t len);

#endif