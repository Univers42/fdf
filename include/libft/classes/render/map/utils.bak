/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:53:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/31 23:16:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

bool realloc_data(t_parser *parser)
{
    t_ctx_data *ctx = parser->context;
    
    if (ctx->values_read >= ctx->array_capacity)
    {
        size_t new_capacity = ctx->array_capacity == 0 ? 64 : ctx->array_capacity * 2;
        
        // Reallocate points array
        if (parser->config.attributes & ATT_VALUE)
        {
            float *new_points = realloc(ctx->points, new_capacity * sizeof(float));
            if (!new_points)
                return false;
            ctx->points = new_points;
        }
        
        // Reallocate colors array
        if (parser->config.attributes & ATT_COLOR)
        {
            uint32_t *new_colors = realloc(ctx->colors, new_capacity * sizeof(uint32_t));
            if (!new_colors)
                return false;
            ctx->colors = new_colors;
        }
        
        // Reallocate strings array
        if (parser->config.attributes & (ATT_NORMAL | ATT_TEXTURE | ATT_FACE | ATT_HEADER | ATT_COMMENT | ATT_CUSTOM))
        {
            char **new_strings = realloc(ctx->strings, new_capacity * sizeof(char*));
            if (!new_strings)
                return false;
            ctx->strings = new_strings;
        }
        
        ctx->array_capacity = new_capacity;
    }
    
    return true;
}

/**
 * this data structure data normally once parsed
 * will collect all teh necesary data to prin
 * we just need to make a assumption on how the data are represented
 * the map are normally represented like in 2D which position
 * are coordonate and teh value inside are the z valu
 * To first see if the parser logic can represent different kind of map
 * we will create a map that can represent easily the simple map up to
 * fdf map
 * ! The map doesn't represent reliably the spaces for now lack of flexibility
 * ! detected
 */
void print_debug(t_parser *parser)
{
    t_ctx_data *ctx;
    int width, height, idx;
    int max_width = 0;
    char temp_str[32];

    ctx = parser->context;
    if (!ctx || !ctx->points || ctx->width <= 0 || ctx->height <= 0) {
        printf("\n❌ No map data to display\n\n");
        return;
    }
    // Defensive: check for overflows
    size_t total = (size_t)ctx->width * (size_t)ctx->height;
    if (ctx->values_read < total)
        total = ctx->values_read;

    // Calculate maximum width needed for formatting
    for (size_t i = 0; i < total; i++) {
        snprintf(temp_str, sizeof(temp_str), "%.0f", ctx->points[i]);
        int len = strlen(temp_str);
        if (len > max_width)
            max_width = len;
    }
    max_width = max_width < 6 ? 6 : max_width; // Minimum width of 6

    // Header
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║                          🗺️  MAP PARSER DEBUG                      ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    printf("║ Dimensions: %dx%d                                                  ║\n", ctx->width, ctx->height);
    printf("║ Total points: %zu                                                  ║\n", ctx->values_read);
    printf("║ Z Range: %.2f → %.2f                                        ║\n", ctx->min_z, ctx->max_z);
    printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

    // Column headers
    printf("     ");
    for (width = 0; width < ctx->width; width++)
    {
        printf("┌%*s┐", max_width, "");
    }
    printf("\n");
    
    printf("     ");
    for (width = 0; width < ctx->width; width++)
    {
        printf("│%*d│", max_width, width);
    }
    printf("\n");
    
    printf("     ");
    for (width = 0; width < ctx->width; width++)
    {
        printf("└%*s┘", max_width, "");
    }
    printf("\n");

    // Map data with row numbers and visual enhancements
    height = -1;
    while (++height < ctx->height)
    {
        // Row separator
        if (height > 0)
        {
            printf("     ");
            for (width = 0; width < ctx->width; width++)
            {
                printf("├%*s┤", max_width, "");
            }
            printf("\n");
        }
        
        // Row number and data
        printf("[%2d] ", height);
        width = -1;
        while (++width < ctx->width)
        {
            idx = height * ctx->width + width;
            if (idx < (int)ctx->values_read && ctx->points && (!ctx->colors || ctx->colors)) {
                float value = ctx->points[idx];
                uint32_t color = (ctx->colors ? ctx->colors[idx] : 0xffffff);
                // Color coding based on value ranges
                const char *color_code = "";
                const char *reset = "\033[0m";
                if (value == 0)
                    color_code = "\033[90m";      // Gray for zero
                else if (value < 10)
                    color_code = "\033[92m";      // Green for low values
                else if (value < 100)
                    color_code = "\033[93m";      // Yellow for medium values
                else if (value < 1000)
                    color_code = "\033[94m";      // Blue for high values
                else
                    color_code = "\033[91m";      // Red for very high values
                // Show color info if not default white
                if (ctx->colors && color != 0xffffff && color != 0)
                    printf("│%s%*.0f\033[35m*%s│", color_code, max_width-1, value, reset);
                else
                    printf("│%s%*.0f%s│", color_code, max_width, value, reset);
            } else {
                // Out of bounds or missing data: print empty cell
                printf("│%*s│", max_width, "");
            }
        }
        printf("\n");
    }
    
    // Bottom border
    printf("     ");
    for (width = 0; width < ctx->width; width++)
    {
        printf("└%*s┘", max_width, "");
    }
    printf("\n");

    // Legend and statistics
    printf("\n📊 Statistics:\n");
    printf("   🟢 Low values (0-9):     ");
    int low_count = 0, med_count = 0, high_count = 0, very_high_count = 0, zero_count = 0;
    for (int i = 0; i < ctx->height * ctx->width && i < (int)ctx->values_read; i++)
    {
        if (ctx->points[i] == 0) zero_count++;
        else if (ctx->points[i] < 10) low_count++;
        else if (ctx->points[i] < 100) med_count++;
        else if (ctx->points[i] < 1000) high_count++;
        else very_high_count++;
    }
    
    printf("%d points\n", low_count);
    printf("   🟡 Medium values (10-99): %d points\n", med_count);
    printf("   🔵 High values (100-999): %d points\n", high_count);
    printf("   🔴 Very high (1000+):     %d points\n", very_high_count);
    printf("   ⚫ Zero values:           %d points\n", zero_count);
    
    if (ctx->colors)
    {
        int colored_points = 0;
        for (int i = 0; i < ctx->height * ctx->width && i < (int)ctx->values_read; i++)
        {
            if (ctx->colors[i] != 0xffffff && ctx->colors[i] != 0)
                colored_points++;
        }
        if (colored_points > 0)
            printf("   🎨 Colored points:        %d points (marked with *)\n", colored_points);
    }
    
    printf("\n✨ Parsing completed successfully!\n\n");
}

void parser_print_debug(t_parser *parser)
{
    print_debug(parser);
}

bool validate_format(t_parser *parser, const char *data, size_t size)
{
	(void)parser;
	(void)data;
	(void)size;
	return true; // Fixed typo: was "retun"
}
