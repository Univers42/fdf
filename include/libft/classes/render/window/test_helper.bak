/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:25:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/03 20:06:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

// Utility functions
void window_put_pixel(t_window *self, int x, int y, int color)
{
    static int debug_pixel_count = 0;
    debug_pixel_count++;
    
    if (debug_pixel_count <= 10)
    {
        printf("🔍 WINDOW_PUT_PIXEL #%d: (%d,%d) = 0x%06X\n", debug_pixel_count, x, y, color);
        printf("   self=%p, img_data=%p\n", self, self ? self->img_data : NULL);
        if (self)
        {
            printf("   window size: %dx%d\n", self->width, self->height);
            printf("   img_ptr=%p, bpp=%d, size_line=%d, endian=%d\n", 
                   self->img_ptr, self->bpp, self->size_line, self->endian);
        }
    }
    
    if (!self || !self->img_data || x < 0 || y < 0 ||
        x >= self->width || y >= self->height)
    {
        if (debug_pixel_count <= 10)
        {
            printf("❌ WINDOW_PUT_PIXEL: Invalid parameters - self=%p, img_data=%p, x=%d, y=%d, w=%d, h=%d\n",
                   self, self ? self->img_data : NULL, x, y,
                   self ? self->width : 0, self ? self->height : 0);
        }
        return;
    }

    // Check MLX image validity
    if (!self->img_ptr)
    {
        if (debug_pixel_count <= 10)
            printf("❌ window_put_pixel: img_ptr is NULL!\n");
        return;
    }

    // Use the correct pixel format for MLX
    char *dst = self->img_data + (y * self->size_line + x * (self->bpp / 8));

    // Verify we're not writing outside the image buffer
    char *buffer_end = self->img_data + (self->size_line * self->height);
    if (dst >= buffer_end)
    {
        if (debug_pixel_count <= 10)
            printf("❌ window_put_pixel: Writing outside buffer! dst=%p, buffer_end=%p\n", dst, buffer_end);
        return;
    }

    // Fix: Use color directly for MLX (no conversion needed)
    unsigned int final_color = color & 0xFFFFFF; // Ensure only RGB bits are used
    *(unsigned int *)dst = final_color;

    if (debug_pixel_count <= 10)
    {
        printf("✅ Put pixel #%d: (%d,%d) = 0x%06X->0x%06X, dst=%p, offset=%ld\n",
               debug_pixel_count, x, y, color, final_color, dst, dst - self->img_data);

        // Verify the write
        unsigned int readback = *(unsigned int *)dst;
        printf("   Readback: 0x%08X %s\n", readback, (readback == final_color) ? "✅" : "❌");
    }
}

int window_get_pixel(t_window *self, int x, int y)
{
    if (!self || !self->img_data || x < 0 || y < 0 ||
        x >= self->width || y >= self->height)
        return 0;

    int *pixel_data = (int *)self->img_data;
    return pixel_data[y * self->width + x];
}

// Simple drawing utilities that don't depend on object system
void window_draw_line_simple(t_window *window, int x0, int y0, int x1, int y1, int color)
{
    if (!window)
        return;

    // Bresenham's line algorithm
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        window_put_pixel(window, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void window_draw_circle_simple(t_window *window, int cx, int cy, int radius, int color)
{
    if (!window || radius <= 0)
        return;

    // Midpoint circle algorithm
    int x = 0;
    int y = radius;
    int d = 1 - radius;

    while (x <= y)
    {
        // Draw 8 octants
        window_put_pixel(window, cx + x, cy + y, color);
        window_put_pixel(window, cx - x, cy + y, color);
        window_put_pixel(window, cx + x, cy - y, color);
        window_put_pixel(window, cx - x, cy - y, color);
        window_put_pixel(window, cx + y, cy + x, color);
        window_put_pixel(window, cx - y, cy + x, color);
        window_put_pixel(window, cx + y, cy - x, color);
        window_put_pixel(window, cx - y, cy - x, color);

        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void window_draw_rectangle_simple(t_window *window, int x, int y, int width, int height, int color)
{
    if (!window || width <= 0 || height <= 0)
        return;

    // Draw rectangle edges
    window_draw_line_simple(window, x, y, x + width - 1, y, color);                           // Top
    window_draw_line_simple(window, x + width - 1, y, x + width - 1, y + height - 1, color);  // Right
    window_draw_line_simple(window, x + width - 1, y + height - 1, x, y + height - 1, color); // Bottom
    window_draw_line_simple(window, x, y + height - 1, x, y, color);                          // Left
}

// Enhanced test basic drawing with z-index simulation
void test_basic_drawing(t_window *window)
{
    printf("=== Enhanced Diagnostic Basic Drawing ===\n");
    printf("Window: %p\n", window);
    printf("Window size: %dx%d\n", window->width, window->height);
    printf("MLX pointers: mlx=%p, win=%p, img=%p\n", window->mlx_ptr, window->win_ptr, window->img_ptr);
    printf("Image data: %p, bpp: %d, size_line: %d, endian: %d\n",
           window->img_data, window->bpp, window->size_line, window->endian);

    // Verify MLX image integrity
    if (!window->img_ptr)
    {
        printf("❌ CRITICAL: img_ptr is NULL! Cannot draw anything!\n");
        return;
    }
    if (!window->img_data)
    {
        printf("❌ CRITICAL: img_data is NULL! Cannot draw anything!\n");
        return;
    }

    // Clear first
    printf("🧹 Clearing window...\n");
    window_clear(window);

    // Test individual pixels with immediate render
    printf("🎯 Testing individual pixels with immediate renders...\n");
    window_put_pixel(window, 50, 50, 0xFF0000); // Red
    window_render(window);
    printf("Drew red pixel at (50,50) - do you see it? Waiting 1 second...\n");
    sleep(1);

    window_put_pixel(window, 51, 50, 0x00FF00); // Green
    window_render(window);
    printf("Drew green pixel at (51,50) - do you see it? Waiting 1 second...\n");
    sleep(1);

    window_put_pixel(window, 52, 50, 0x0000FF); // Blue
    window_render(window);
    printf("Drew blue pixel at (52,50) - do you see it? Waiting 1 second...\n");
    sleep(1);

    window_put_pixel(window, 53, 50, 0xFFFFFF); // White
    window_render(window);
    printf("Drew white pixel at (53,50) - do you see it? Waiting 1 second...\n");
    sleep(1);

    // Test with a small filled rectangle instead of lines
    printf("🟥 Drawing a small red rectangle...\n");
    for (int y = 100; y < 110; y++)
    {
        for (int x = 100; x < 110; x++)
        {
            window_put_pixel(window, x, y, 0xFF0000);
        }
    }
    window_render(window);
    printf("Drew 10x10 red rectangle at (100,100) - do you see it? Waiting 2 seconds...\n");
    sleep(2);

    // Test with larger shapes
    printf("🟢 Drawing larger green rectangle...\n");
    for (int y = 200; y < 250; y++)
    {
        for (int x = 200; x < 250; x++)
        {
            window_put_pixel(window, x, y, 0x00FF00);
        }
    }
    window_render(window);
    printf("Drew 50x50 green rectangle at (200,200) - do you see it? Waiting 2 seconds...\n");
    sleep(2);

    printf("✅ Enhanced diagnostic drawing completed.\n");
    printf("If you still don't see anything, the issue is likely with MLX image display.\n");
}
