/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:20:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/31 23:38:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "ft_stdlib.h"

bool parse_chunk(t_parser *parser, const char *data, size_t size)
{
    t_ctx_data *ctx_data = parser->context;
    size_t i = 0;

    while (i < size)
    {
        // Skip whitespace and delimiters
        i = skip_delimiters(data, size, i);
        if (i >= size)
            break;

        // Handle newlines
        if (data[i] == '\n') {
            if (!advance_line(parser)) {
                return false;
            }
            i++;
            continue;
        }

        // Parse value (z_val)
        if (!parse_val(parser, data, &i)) {
            return false;
        }

        // Ensure we have space in arrays
        if (!realloc_data(parser)) {
            return false;
        }

        // Store the parsed value and color
        ctx_data->points[ctx_data->values_read] = (float)ctx_data->z;
        ctx_data->colors[ctx_data->values_read] = ctx_data->current_color;

        // Update min/max Z values
        if (!ctx_data->z_set || ctx_data->z < ctx_data->min_z)
            ctx_data->min_z = ctx_data->z;
        if (!ctx_data->z_set || ctx_data->z > ctx_data->max_z)
            ctx_data->max_z = ctx_data->z;
        ctx_data->z_set = true;

        ctx_data->values_read++;
        ctx_data->x++;

        // Skip remaining spaces on the line
        while (i < size && data[i] == ' ')
            i++;
    }
    
    return true;
}
