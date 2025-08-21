/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:17:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/01 01:55:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdbool.h>

// Forward declarations (if not included elsewhere)
bool parse_numeric_value(t_parser *parser);
bool parse_color_value(t_parser *parser);

void fsm_handle_space(t_parser *parser)
{
    parser->position = skip_parser_delimiters(parser, parser->position);
}

void fsm_handle_val(t_parser *parser)
{
    t_ctx_data *ctx = parser->context;
    if (!parse_numeric_value(parser))
        return;

    if (!realloc_parser_data(parser))
        return;

    ctx->points[ctx->values_read] = (float)ctx->z;

    if (!ctx->z_set || ctx->z < ctx->min_z)
        ctx->min_z = ctx->z;
    if (!ctx->z_set || ctx->z > ctx->max_z)
        ctx->max_z = ctx->z;
    ctx->z_set = true;

    ctx->values_read++;
    ctx->x++;
}

void fsm_handle_color(t_parser *parser)
{
    (void)parse_color_value(parser);
}

void fsm_handle_word(t_parser *parser)
{
    while (parser->position < parser->buffer_size &&
           !is_parser_delimiter(parser, parser->buffer[parser->position]))
        parser->position++;
}