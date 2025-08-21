#include "object.h"
#include <math.h>

// Forward declarations for window functions
void window_put_pixel(t_window *window, int x, int y, int color);
void window_draw_line_simple(t_window *window, int x0, int y0, int x1, int y1, int color);
void window_draw_circle_simple(t_window *window, int cx, int cy, int radius, int color);
void window_draw_rectangle_simple(t_window *window, int x, int y, int width, int height, int color);

void draw_line(t_window *window, t_point3d start, t_point3d end, int color)
{
    if (!window)
        return;
    window_draw_line_simple(window, (int)start.x, (int)start.y, (int)end.x, (int)end.y, color);
}

void draw_circle(t_window *window, t_point3d center, float radius, int color)
{
    if (!window)
        return;
    window_draw_circle_simple(window, (int)center.x, (int)center.y, (int)radius, color);
}

void draw_rectangle(t_window *window, t_point3d pos, float width, float height, int color)
{
    if (!window)
        return;
    window_draw_rectangle_simple(window, (int)pos.x, (int)pos.y, (int)width, (int)height, color);
}
