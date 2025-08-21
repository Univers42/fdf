/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:52:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 19:53:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "window.h" // Add this to get the full definition of struct s_method

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

// Forward declarations
typedef struct s_parser t_parser;
typedef struct s_method t_method;
typedef struct s_ctx_data t_ctx_data;

typedef enum e_format_type
{
    FORMAT_NUMBER,
    FORMAT_STRING,
    FORMAT_HEXADECIMAL,
    FORMAT_DECIMAL,
    FORMAT_OCTAL,
    FORMAT_CUSTOM
} t_format_type;

typedef enum e_delimiter
{
    DELIM_SPACE = ' ',
    DELIM_COMMA = ',',
    DELIM_TAB = '\t',
    DELIM_PIPE = '|',
    DELIM_COLON = ':',
    DELIM_SEMICOLON = ';',
    DELIM_SLASH = '/',
    DELIM_CUSTOM = 0
} t_delimiter;

typedef enum e_att
{
    ATT_VALUE     = 1 << 0,  // Z values (mandatory)
    ATT_COLOR     = 1 << 1,  // Color values
    ATT_NORMAL    = 1 << 2,  // Normal vectors
    ATT_TEXTURE   = 1 << 3,  // Texture coordinates
    ATT_FACE      = 1 << 4,  // Face indices
    ATT_HEADER    = 1 << 5,  // Header information
    ATT_COMMENT   = 1 << 6,  // Comments
    ATT_CUSTOM    = 1 << 7   // Custom attributes
} t_att;

typedef struct s_parser_config
{
    t_format_type   format;
    t_delimiter     delimiter;
    uint32_t        attributes;
    char            custom_delimiter;
    bool            skip_whitespace;
    bool            case_sensitive;
} t_parser_config;

typedef struct s_token
{
    t_att           attribute;
    t_format_type   format;
    union {
        int         int_val;
        float       float_val;
        uint32_t    color_val;
        char        *string_val;
    } data;
    size_t          position;
    bool            valid;
} t_token;

typedef struct s_vmap
{
    bool    (*parse)(t_parser *parser);
    bool    (*parse_token)(t_parser *parser, t_token *token);
    bool    (*parse_value)(t_parser *parser, t_token *token);
    bool    (*parse_color)(t_parser *parser, t_token *token);
    bool    (*parse_string)(t_parser *parser, t_token *token);
    bool    (*finalize)(t_parser *parser);
    void    (*cleanup)(t_parser *parser);
    bool    (*realloc_data)(t_parser *parser);
    void    (*print_debug)(t_parser *parser);
    bool    (*advance_line)(t_parser *parser);
    size_t  (*skip_delimiter)(t_parser *parser, size_t pos);
    bool    (*is_delimiter)(t_parser *parser, char c);
    bool    (*validate_format)(t_parser *parser, const char *data, size_t size);
} t_vmap;

typedef struct s_ctx_data
{
    float       *points;
    uint32_t    *colors;
    char        **strings;
    int         width;
    int         height;
    int         x;
    int         y;
    int         z;
    float       current_z;
    uint32_t    current_color;
    char        *current_string;
    float       min_z;
    float       max_z;
    bool        z_set;
    bool        width_set;
    size_t      values_read;
    size_t      array_capacity;
    t_token     *tokens;
    size_t      tokens_count;
    size_t      token_capacity;
} t_ctx_data;

typedef struct s_parser
{
    t_vmap              *method; // <-- change from t_method * to t_vmap *
    t_parser_config     config;
    char                *buffer;
    char                *error_message;
    t_ctx_data          *context;
    size_t              buffer_size;
    size_t              buffer_capacity;
    size_t              position;
    bool                error_state;
    char                *filename;
} t_parser;

// Core API - The 4 parameter constructor you requested
t_parser    *parser_create(const char *filename, t_format_type format, 
                          t_delimiter delimiter, uint32_t attributes);
void        parser_destroy(t_parser *parser);
bool        parser_parse(t_parser *parser);
void        parser_print_debug(t_parser *parser);

// Internal functions
bool        parse_chunk(t_parser *parser, const char *data, size_t size);
bool        parse_value_token(t_parser *parser, t_token *token);
bool        parse_color_token(t_parser *parser, t_token *token);
bool        finalize_parsing(t_parser *parser);
bool        is_parser_delimiter(t_parser *parser, char c);
bool        realloc_parser_data(t_parser *parser);
size_t      skip_parser_delimiters(t_parser *parser, size_t offset);
bool        advance_parser_line(t_parser *parser);
bool        validate_parser_format(t_parser *parser, const char *data, size_t size);
void        cleanup_parser(t_parser *parser);
t_vmap      *get_parser_method(void); // <-- fix prototype to match implementation
void        parser_cleanup(t_parser *parser); // <-- add prototype

// Add these prototypes for legacy/basic parser support:
bool        parse_val(t_parser *parser, const char *data, size_t *offset);
bool        parse_color(t_parser *parser, const char *data, size_t *offset);
bool        realloc_data(t_parser *parser);
size_t      skip_delimiters(const char *data, size_t size, size_t offset);
bool        advance_line(t_parser *parser);
bool		store_parsed_color(t_parser *parser, t_token *token);
bool		parse_token_sequence(t_parser *parser);
bool		parse_main_loop(t_parser *parser);
t_ctx_data *create_parser_context(uint32_t attributes);
bool		load_file_into_parser(t_parser *parser, const char *filename);
#endif