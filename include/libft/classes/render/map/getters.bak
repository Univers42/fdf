/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:16:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/01 00:04:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

bool is_delimiter(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

size_t skip_delimiters(const char *data, size_t size, size_t offset)
{
    while (offset < size) {
        char c = data[offset];
        // Skip spaces and tabs, but NOT newlines (those are handled separately)
        if (c == ' ' || c == '\t') {
            offset++;
        } else {
            break;
        }
    }
    return offset;
}

bool validate_parser_format(t_parser *parser, const char *data, size_t size)
{
    (void)parser;
    (void)data;
    (void)size;
    return true;
}

size_t skip_parser_delimiters(t_parser *parser, size_t offset)
{
    while (offset < parser->buffer_size) {
        char c = parser->buffer[offset];
        
        // Always skip whitespace if enabled
        if (parser->config.skip_whitespace && (c == ' ' || c == '\t')) {
            offset++;
            continue;
        }
        
        // Skip configured delimiter
        if (is_parser_delimiter(parser, c)) {
            offset++;
            continue;
        }
        
        break;
    }
    
    return offset;
}


bool is_parser_delimiter(t_parser *parser, char c)
{
    // Accept both space and comma as delimiters if either is configured
    if (parser->config.delimiter == DELIM_SPACE || parser->config.delimiter == DELIM_COMMA) {
        return c == ' ' || c == ',';
    }
    if (parser->config.delimiter == DELIM_CUSTOM) {
        return c == parser->config.custom_delimiter;
    }
    return c == (char)parser->config.delimiter;
}

bool realloc_parser_data(t_parser *parser)
{
    t_ctx_data *ctx = parser->context;
    
    if (ctx->values_read >= ctx->array_capacity) {
        size_t new_capacity = ctx->array_capacity * 2;
        
        if (parser->config.attributes & ATT_VALUE) {
            float *new_points = realloc(ctx->points, new_capacity * sizeof(float));
            if (!new_points)
                return false;
            ctx->points = new_points;
        }
        
        if (parser->config.attributes & ATT_COLOR) {
            uint32_t *new_colors = realloc(ctx->colors, new_capacity * sizeof(uint32_t));
            if (!new_colors)
                return false;
            ctx->colors = new_colors;
        }
        
        ctx->array_capacity = new_capacity;
    }
    
    return true;
}

bool load_file_into_parser(t_parser *parser, const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return false;
    
    struct stat st;
    if (fstat(fd, &st) != 0) {
        close(fd);
        return false;
    }
    
    size_t filesize = (size_t)st.st_size;
    if (filesize > parser->buffer_capacity) {
        char *newbuf = realloc(parser->buffer, filesize + 1);
        if (!newbuf) {
            close(fd);
            return false;
        }
        parser->buffer = newbuf;
        parser->buffer_capacity = filesize + 1;
    }
    
    ssize_t n = read(fd, parser->buffer, filesize);
    close(fd);
    
    if (n < 0)
        return false;
    
    parser->buffer_size = (size_t)n;
    parser->buffer[parser->buffer_size] = '\0';
    return true;
}