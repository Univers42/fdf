/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:27:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/01 00:10:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <mapfile> [format] [delimiter] [attributes]\n", argv[0]);
        printf("Formats: decimal(0), octal(1), hex(2)\n");
        printf("Delimiters: space(32), comma(44), pipe(124), semicolon(59)\n");
        printf("Attributes: value(1), color(2), normal(4), etc.\n");
        return 1;
    }

    // Check if file exists and is readable
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    fclose(f);

    // Parse command line arguments with defaults
    t_format_type format = FORMAT_DECIMAL;
    t_delimiter delimiter = DELIM_SPACE; // default
    uint32_t attributes = ATT_VALUE; // Default: values and color
    
    // Use command-line or default to ATT_VALUE | ATT_COLOR
    if (argc > 2) format = (t_format_type)atoi(argv[2]);
    if (argc > 3) delimiter = (t_delimiter)atoi(argv[3]);
    else delimiter = DELIM_SPACE; // or DELIM_COMMA if you want comma as default
    if (argc > 4) attributes = (uint32_t)atoi(argv[4]);

    // Create parser with 4 parameters as requested
    t_parser *parser = parser_create(argv[1], format, delimiter, attributes);
    if (!parser) {
        printf("Failed to create parser for %s\n", argv[1]);
        return 1;
    }
    
    // Parse the file
    if (!parser_parse(parser)) {
        printf("Parsing failed: %s\n", 
               parser->error_message ? parser->error_message : "Unknown error");
        parser_destroy(parser);
        return 1;
    }
    // Print debug info
    parser_print_debug(parser);
    parser_destroy(parser);
    return 0;
}
