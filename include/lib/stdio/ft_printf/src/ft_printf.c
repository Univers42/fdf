/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:45:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 14:09:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "writer.h"

int	ft_vfprintf(int fd, const char *format, va_list *ap)
{
	static t_writer			buf_out;
	int						return_value;
	t_parser				parser;

	if (format == NULL || fd < 0)
		return (-1);
	buf_out.fd = fd;
	return_value = parser_parse_and_write(&parser, format, ap, &buf_out);
	return (return_value);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		return_value;

	va_start(ap, format);
	return_value = ft_vfprintf(fd, format, &ap);
	va_end(ap);
	return (return_value);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		return_value;

	va_start(ap, format);
	return_value = ft_vfprintf(1, format, &ap);
	va_end(ap);
	return (return_value);
}
