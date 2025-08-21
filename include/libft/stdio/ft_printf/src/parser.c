/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:46:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:53:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include "ft_memory.h"

static void	parser_initialize(
		t_parser *parser,
		const char *format_str,
		va_list *params,
		t_writer *buf_out
) {
	parser->writer = buf_out;
	parser->index = 0;
	parser->format = format_str;
	parser->ap = params;
	ft_memset(&parser->token_meta, 0, sizeof(t_token_meta));
}

int	parser_parse_and_write(
		t_parser *parser,
		const char *format_str,
		va_list *params,
		t_writer *buf_out
) {
	size_t	token_idx;

	parser_initialize(parser, format_str, params, buf_out);
	writer_reset(parser->writer);
	while (parser->format[parser->index] != '\0')
	{
		if (parser->format[parser->index] != '%')
		{
			writer_putchar(parser->writer, parser->format[parser->index]);
			++parser->index;
		}
		else
		{
			token_idx = ++parser->index;
			if (!parser_process_token(parser))
			{
				writer_putchar(parser->writer, '%');
				parser->index = token_idx;
			}
		}
	}
	writer_flush(parser->writer);
	if (parser->writer->error < 0)
		return (parser->writer->error < 0);
	return (parser->writer->n_written);
}
