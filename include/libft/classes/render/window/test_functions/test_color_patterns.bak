/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_color_patterns.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:47:29 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 19:49:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

// Test drawing functions
void test_basic_drawing(t_window *window)
{
    printf("Testing basic drawing functions...\n");
    printf("Window size: %dx%d\n", window->width, window->height);
    printf("Image data: %p\n", window->img_data);
    // Draw some test shapes - use righter colors and make sure they're in bounds
    printf("Drawing red line...\n");
    window_draw_line_simple(window, 50, 50, 200, 100, 0xFF0000); // Red lin
    printf("Drawing green circle...\n");
    window_draw_circle_simple(window, 150, 200, 50, 0x00FF00); // Green circle
    printf("Drawing blue rectangle...\n");
    window_draw_rectangle_simple(window, 250, 150, 100, 80, 0x0000FF); // Blue rectangle
    printf("Drawing grid...\n");
    for (int i = 0; i < window->width && i < 800; i += 50)
        window_draw_line_simple(window, i, 0, i, window->height < 600 ? window->height : 600, 0x404040);
    for (int i = 0; i < window->height && i < 600; i += 50)
        window_draw_line_simple(window, 0, i, window->width < 800 ? window->width : 800, i, 0x404040);
    printf("Basic drawing completed.\n");
}
