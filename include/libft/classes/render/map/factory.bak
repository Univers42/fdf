/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:20:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/01 07:50:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

bool file_is_readable(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return false;
    close(fd);
    return true;
}

// Helper: load file content into parser->buffer, set parser->buffer_size
static bool load_file_content(t_parser *parser, const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return false;

    struct stat st;
    if (fstat(fd, &st) != 0)
    {
        close(fd);
        return false;
    }
    size_t filesize = (size_t)st.st_size;
    if (filesize > parser->buffer_capacity)
    {
        char *newbuf = realloc(parser->buffer, filesize + 1);
        if (!newbuf)
        {
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

// Helper: cleanup parser on failure
static void cleanup_failed_parser(t_parser *parser)
{
    if (!parser) return;
    if (parser->buffer) free(parser->buffer);
    if (parser->filename) free(parser->filename);
    if (parser->context) {
        if (parser->context->points) free(parser->context->points);
        if (parser->context->colors) free(parser->context->colors);
        if (parser->context->strings) {
            for (size_t i = 0; i < parser->context->values_read; i++)
                free(parser->context->strings[i]);
            free(parser->context->strings);
        }
        free(parser->context);
    }
    free(parser);
}

t_parser *parser_factory(uint32_t attributes, const char *filename)
{
    t_parser *parser = malloc(sizeof(t_parser));
    if (!parser)
        return NULL;

    parser->method = get_parser_method();
    parser->buffer_capacity = BUFFER_SIZE;
    parser->buffer = malloc(parser->buffer_capacity);
    parser->buffer_size = 0;
    parser->position = 0;
    parser->error_state = false;
    parser->error_message = NULL;
    parser->filename = NULL;
    parser->context = NULL;

    if (!parser->buffer)
    {
        free(parser);
        return NULL;
    }

    if (filename)
    {
        parser->filename = strdup(filename);
        if (!parser->filename || !load_file_content(parser, filename))
        {
            cleanup_failed_parser(parser);
            return NULL;
        }
    }

    // Allocate context and arrays as needed
    parser->context = malloc(sizeof(t_ctx_data));
    if (!parser->context)
    {
        cleanup_failed_parser(parser);
        return NULL;
    }
    memset(parser->context, 0, sizeof(t_ctx_data));
    parser->context->current_color = 0xffffff;
    parser->context->array_capacity = 64;
    if (attributes & ATT_VALUE) {
        parser->context->points = malloc(parser->context->array_capacity * sizeof(float));
        if (!parser->context->points) {
            cleanup_failed_parser(parser);
            return NULL;
        }
    }
    if (attributes & ATT_COLOR) {
        parser->context->colors = malloc(parser->context->array_capacity * sizeof(uint32_t));
        if (!parser->context->colors) {
            cleanup_failed_parser(parser);
            return NULL;
        }
    }
    if (attributes & (ATT_NORMAL | ATT_TEXTURE | ATT_FACE | ATT_HEADER | ATT_COMMENT | ATT_CUSTOM)) {
        parser->context->strings = malloc(parser->context->array_capacity * sizeof(char*));
        if (!parser->context->strings) {
            cleanup_failed_parser(parser);
            return NULL;
        }
    }
    parser->config.attributes = attributes;

    return parser;
}
