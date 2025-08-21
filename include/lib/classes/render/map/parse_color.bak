/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:20:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/31 23:48:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "ft_stdlib.h"

bool parse_token_sequence(t_parser *parser);

bool parse_color(t_parser *parser, const char *data, size_t *offset)
{
    t_ctx_data *ctx_parser = parser->context;

    // Check if there's a comma for color
    if (*offset < parser->buffer_size && data[*offset] == ',') {
        (*offset)++; // Skip comma

        uint32_t color = 0;
        int hex_digits = 0;

        // Accept both 0x and 0X as prefix (case-insensitive)
        if (*offset + 1 < parser->buffer_size &&
            data[*offset] == '0' &&
            (data[*offset + 1] == 'x' || data[*offset + 1] == 'X')) {
            *offset += 2;
        }

        // Accept up to 6 hex digits (0-9, a-f, A-F)
        while (*offset < parser->buffer_size && hex_digits < 6) {
            char c = data[*offset];
            if ((c >= '0' && c <= '9') ||
                (c >= 'a' && c <= 'f') ||
                (c >= 'A' && c <= 'F')) {
                color = (color << 4) | (unsigned int)(
                    (c >= '0' && c <= '9') ? (c - '0') :
                    (c >= 'a' && c <= 'f') ? (c - 'a' + 10) :
                    (c - 'A' + 10)
                );
                (*offset)++;
                hex_digits++;
            } else {
                break; // End of hex digits
            }
        }

        if (hex_digits == 0) {
            parser->error_message = strdup("Invalid color format after comma");
            return false; // Invalid color format
        }

        // If only 3 hex digits, expand to 6 (e.g. fff -> ffffff)
        if (hex_digits == 3) {
            color = ((color & 0xF00) << 8) | ((color & 0xF0) << 4) | (color & 0xF);
            color = ((color & 0xF00000) >> 12) | ((color & 0xF000) >> 8) | ((color & 0xF0) >> 4) |
                    ((color & 0xF00) << 8) | ((color & 0xF0) << 4) | (color & 0xF);
            // But for FDF, just repeat each nibble: 0xabc -> 0xaabbcc
            unsigned int r = (color >> 8) & 0xF;
            unsigned int g = (color >> 4) & 0xF;
            unsigned int b = color & 0xF;
            color = (r << 20) | (r << 16) | (g << 12) | (g << 8) | (b << 4) | b;
        }

        ctx_parser->current_color = color;
    } else {
        // No color specified, use default white
        ctx_parser->current_color = 0xffffff;
    }

    return true;
}

bool parse_main_loop(t_parser *parser)
{
    parser->position = 0;
    
    while (parser->position < parser->buffer_size) {
        // Skip whitespace and delimiters at start
        parser->position = parser->method->skip_delimiter(parser, parser->position);
        
        if (parser->position >= parser->buffer_size)
            break;
        
        // Handle newlines
        if (parser->buffer[parser->position] == '\n') {
            if (!parser->method->advance_line(parser))
                return false;
            parser->position++;
            continue;
        }
        
        // Parse tokens based on configuration
        if (!parse_token_sequence(parser))
            return false;
    }
    
    return parser->method->finalize(parser);
}