/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:52:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 15:54:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

// Parse hexadecimal color
bool parse_color_token(t_parser *parser, t_token *token)
{
    size_t pos = parser->position;
    uint32_t color = 0;
    int hex_digits = 0;
    
    // Skip 0x prefix if present
    if (pos + 1 < parser->buffer_size && 
        parser->buffer[pos] == '0' && 
        (parser->buffer[pos + 1] == 'x' || parser->buffer[pos + 1] == 'X')) {
        pos += 2;
    }
    
    // Parse hex digits
    while (pos < parser->buffer_size && hex_digits < 8) {
        char c = parser->buffer[pos];
        if (c >= '0' && c <= '9') {
            color = (color << 4) | (c - '0');
        } else if (c >= 'a' && c <= 'f') {
            color = (color << 4) | (c - 'a' + 10);
        } else if (c >= 'A' && c <= 'F') {
            color = (color << 4) | (c - 'A' + 10);
        } else {
            break;
        }
        pos++;
        hex_digits++;
    }
    
    if (hex_digits == 0)
        return false;
    
    token->attribute = ATT_COLOR;
    token->format = FORMAT_HEXADECIMAL;
    token->data.color_val = color;
    token->position = parser->position;
    token->valid = true;
    
    parser->position = pos;
    parser->context->current_color = color;
    
    return true;
}

bool store_parsed_value(t_parser *parser, t_token *token)
{
    t_ctx_data *ctx = parser->context;
    
    if (!parser->method->realloc_data(parser))
        return false;
    
    ctx->points[ctx->values_read] = (float)token->data.int_val;
    
    // Update min/max
    if (!ctx->z_set || token->data.int_val < ctx->min_z) {
        ctx->min_z = token->data.int_val;
    }
    if (!ctx->z_set || token->data.int_val > ctx->max_z) {
        ctx->max_z = token->data.int_val;
    }
    ctx->z_set = true;
    
    ctx->values_read++;
    ctx->x++;
    
    return true;
}

bool parse_value_token(t_parser *parser, t_token *token)
{
    size_t pos = parser->position;
    int value = 0;
    bool negative = false;
    bool has_digits = false;

    // Handle sign
    if (pos < parser->buffer_size && parser->buffer[pos] == '-') {
        negative = true;
        pos++;
    } else if (pos < parser->buffer_size && parser->buffer[pos] == '+') {
        pos++;
    }

    // Parse based on format
    switch (parser->config.format) {
        case FORMAT_DECIMAL:
        case FORMAT_NUMBER:
            while (pos < parser->buffer_size && 
                   parser->buffer[pos] >= '0' && parser->buffer[pos] <= '9') {
                value = value * 10 + (parser->buffer[pos] - '0');
                pos++;
                has_digits = true;
            }
            break;
        case FORMAT_OCTAL:
            while (pos < parser->buffer_size && 
                   parser->buffer[pos] >= '0' && parser->buffer[pos] <= '7') {
                value = value * 8 + (parser->buffer[pos] - '0');
                pos++;
                has_digits = true;
            }
            break;
        case FORMAT_HEXADECIMAL:
            if (pos + 1 < parser->buffer_size && 
                parser->buffer[pos] == '0' && 
                (parser->buffer[pos + 1] == 'x' || parser->buffer[pos + 1] == 'X')) {
                pos += 2;
            }
            while (pos < parser->buffer_size) {
                char c = parser->buffer[pos];
                if (c >= '0' && c <= '9') {
                    value = value * 16 + (c - '0');
                    has_digits = true;
                } else if (c >= 'a' && c <= 'f') {
                    value = value * 16 + (c - 'a' + 10);
                    has_digits = true;
                } else if (c >= 'A' && c <= 'F') {
                    value = value * 16 + (c - 'A' + 10);
                    has_digits = true;
                } else {
                    break;
                }
                pos++;
            }
            break;
        default:
            parser->error_message = strdup("Unknown format in parse_value_token");
            return false;
    }

    // Print debug info if parse fails
    if (!has_digits) {
        char dbg[128];
        snprintf(dbg, sizeof(dbg), "No digits found in parse_value_token at pos %zu: '%c'", pos, parser->buffer[pos]);
        parser->error_message = strdup(dbg);
        return false;
    }

    // Store result
    token->attribute = ATT_VALUE;
    token->format = parser->config.format;
    token->data.int_val = negative ? -value : value;
    token->position = parser->position;
    token->valid = true;

    parser->position = pos;
    parser->context->z = negative ? -value : value;
    parser->context->current_z = (float)(negative ? -value : value);

    return true;
}

bool parser_parse(t_parser *parser)
{
    // Call the real main loop, not the method table!
    return parse_main_loop(parser);
}


// Parse string
bool enhanced_parse_string(t_parser *parser, t_token *token)
{
    size_t pos = parser->position;
    size_t start = pos;

    while (pos < parser->buffer_size)
    {
        char c = parser->buffer[pos];
        if (is_parser_delimiter(parser, c) || c == '\n' ||
            (parser->config.skip_whitespace && (c == ' ' || c == '\t')))
            break;
        pos++;
    }
    
    if (pos == start)
        return false;
    
    size_t len = pos - start;
    char *str = malloc(len + 1);
    if (!str)
        return false;
    
    strncpy(str, &parser->buffer[start], len);
    str[len] = '\0';
    
    token->attribute = ATT_NORMAL;
    token->format = FORMAT_STRING;
    token->data.string_val = str;
    token->position = parser->position;
    token->valid = true;
    
    parser->position = pos;
    
    return true;
}

// Enhanced token parsing
bool enhanced_parse_token(t_parser *parser, t_token *token)
{
    // Initialize token
    memset(token, 0, sizeof(t_token));
    
    // Skip delimiters
    parser->position = skip_parser_delimiters(parser, parser->position);
    
    if (parser->position >= parser->buffer_size)
        return false;
    
    char current = parser->buffer[parser->position];
    
    // Determine what to parse based on current character and configuration
    
    // Check for color (starts with comma or 0x)
    if ((parser->config.attributes & ATT_COLOR) && 
        (current == ',' || (current == '0' && parser->position + 1 < parser->buffer_size && 
         (parser->buffer[parser->position + 1] == 'x' || parser->buffer[parser->position + 1] == 'X'))))
    {
        return parse_color_token(parser, token);
    }
    
    // Check for numeric value
    if ((parser->config.attributes & ATT_VALUE) && 
        (current == '-' || current == '+' || (current >= '0' && current <= '9')))
    {
        return parse_value_token(parser, token);
    }
    
    // Parse as string if other attributes are enabled
    if (parser->config.attributes & (ATT_NORMAL | ATT_TEXTURE | ATT_FACE | ATT_HEADER | ATT_COMMENT | ATT_CUSTOM))
    {
        return enhanced_parse_string(parser, token);
    }
    
    return false;
}

// Remove or comment out this function if you have it in utils.c
bool advance_parser_line(t_parser *parser)
{
    t_ctx_data *ctx = parser->context;
    
    if (!ctx->width_set && ctx->x > 0) {
        ctx->width = ctx->x;
        ctx->width_set = true;
    }
    
    ctx->x = 0;
    ctx->y++;
    ctx->height++;
    
    return true;
}

bool finalize_parsing(t_parser *parser)
{
    t_ctx_data *ctx = parser->context;

    if (ctx->x > 0 && !advance_parser_line(parser))
        return false;

    // Only error if ATT_COLOR is set and at least one value in the map uses a color
    if (parser->config.attributes & ATT_COLOR) {
        //bool has_any_color = false;
        bool has_non_default = false;
        for (size_t i = 0; i < ctx->values_read; i++) {
            if (ctx->colors && ctx->colors[i] != 0xffffff && ctx->colors[i] != 0) {
                has_non_default = true;
            }
            if (ctx->colors && ctx->colors[i] != 0) {
                //has_any_color = true;
            }
        }
        // If no color is present at all, but ATT_COLOR is set, allow it (FDF style)
        // Only error if some values have color and some don't (mixed), or if you want strict mode
        // Here: only error if ATT_COLOR is set and NO color is present AND at least one value had a comma
        if (!has_non_default /* no explicit color found */) {
            // Accept maps with only default colors (all white)
            return true;
        }
        // Otherwise, if you want strict mode (all must have color), you can add more checks here
    }
    return true;
}

t_parser *parser_create(const char *filename, t_format_type format, 
                       t_delimiter delimiter, uint32_t attributes)
{
    if (!filename || !(attributes & ATT_VALUE)) {
        // ATT_VALUE is mandatory - we need at least Z values
        return NULL;
    }
    
    t_parser *parser = malloc(sizeof(t_parser));
    if (!parser)
        return NULL;
    
    // Initialize parser
    memset(parser, 0, sizeof(t_parser));
    parser->method = get_parser_method();
    
    // Set configuration
    parser->config.format = format;
    parser->config.delimiter = delimiter;
    parser->config.attributes = attributes;
    parser->config.skip_whitespace = true;
    parser->config.case_sensitive = false;
    
    // Initialize buffer
    parser->buffer_capacity = BUFFER_SIZE;
    parser->buffer = malloc(parser->buffer_capacity);
    if (!parser->buffer) {
        free(parser);
        return NULL;
    }
    
    // Load file
    parser->filename = strdup(filename);
    if (!load_file_into_parser(parser, filename)) {
        cleanup_parser(parser);
        free(parser);
        return NULL;
    }
    
    // Create context
    parser->context = create_parser_context(attributes);
    if (!parser->context) {
        cleanup_parser(parser);
        free(parser);
        return NULL;
    }
    
    return parser;
}

bool parse_token_sequence(t_parser *parser)
{
    t_token token;

    if (!parser->method->parse_value(parser, &token)) {
        parser->error_message = strdup("Failed to parse value");
        return false;
    }

    if (!store_parsed_value(parser, &token)) {
        parser->error_message = strdup("Failed to store parsed value");
        return false;
    }

    // Accept comma before color, regardless of delimiter
    while (parser->position < parser->buffer_size &&
           parser->buffer[parser->position] != '\n' &&
           parser->buffer[parser->position] != ' ')
    {
        char c = parser->buffer[parser->position];

        // Accept comma for color, or the configured delimiter for other attributes
        if (c == ',' && (parser->config.attributes & ATT_COLOR)) {
            parser->position++; // Skip comma
            if (parse_color_token(parser, &token)) {
                store_parsed_color(parser, &token);
            } else {
                parser->error_message = strdup("Invalid color after comma");
                return false;
            }
            continue;
        }
        // For other attributes, only accept the configured delimiter
        if (!parser->method->is_delimiter(parser, c)) {
            char dbg[128];
            snprintf(dbg, sizeof(dbg), "Unexpected character '%c' at pos %zu, expected delimiter", c, parser->position);
            parser->error_message = strdup(dbg);
            return false;
        }

        parser->position++; // Skip delimiter
        break; // Only one delimiter/attribute allowed after value
    }

    return true;
}