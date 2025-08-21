/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:06:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/01 07:52:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_vmap *get_parser_method(void)
{
    static t_vmap method = {
        .parse = parser_parse,
        .parse_token = NULL,
        .parse_value = parse_value_token,
        .parse_color = parse_color_token,
        .parse_string = NULL,
        .finalize = finalize_parsing,
        .cleanup = parser_cleanup,
        .realloc_data = realloc_parser_data,
        .print_debug = parser_print_debug,
        .advance_line = advance_parser_line,
        .skip_delimiter = skip_parser_delimiters,
        .is_delimiter = is_parser_delimiter,
        .validate_format = validate_parser_format
    };
    return &method;
}

void parser_destroy(t_parser *parser)
{
    if (!parser)
        return;
    if (parser->method && parser->method->cleanup)
        parser->method->cleanup(parser);
    free(parser);
}

void parser_cleanup(t_parser *parser)
{
    if (!parser)
        return;
    // Actual cleanup logic here
    cleanup_parser(parser);
}

void cleanup_parser(t_parser *parser)
{
    if (!parser)
        return;
    if (parser->context) {
        free(parser->context->points);
        free(parser->context->colors);
        if (parser->context->strings) {
            for (size_t i = 0; i < parser->context->values_read; i++) {
                free(parser->context->strings[i]);
            }
            free(parser->context->strings);
        }
        free(parser->context);
    }
    free(parser->buffer);
    free(parser->error_message);
    free(parser->filename);
}

bool advance_line(t_parser *parser)
{
    t_ctx_data *ctx = parser->context;
    
    // Set width on first line
    if (!ctx->width_set && ctx->x > 0) {
        ctx->width = ctx->x;
        ctx->width_set = true;
    }
    
    // Reset x position and increment y/height
    ctx->x = 0;
    ctx->y++;
    ctx->height++;
    
    return true;
}