// This file contains the essential object functions needed by the linker
#include "object.h"
#include <string.h>

// Forward declarations for window functions
void window_put_pixel(t_window *window, int x, int y, int color);
void window_draw_line_simple(t_window *window, int x0, int y0, int x1, int y1, int color);
void window_draw_circle_simple(t_window *window, int cx, int cy, int radius, int color);
void window_draw_rectangle_simple(t_window *window, int x, int y, int width, int height, int color);

// These functions are needed by visual_test.c but were in drawing_utils.c
// We need to ensure they're available to the linker

// Public API wrapper functions - these delegate to the vtable
t_object *object_new(t_object_type type)
{
    return g_object_vtable.new(type);
}

void object_destroy(t_object *self)
{
    if (self && self->vtable)
        self->vtable->destroy(self);
}

void object_draw(t_object *self, t_window *window)
{
    if (self && self->vtable)
        self->vtable->draw(self, window);
}

void object_update(t_object *self, float delta_time)
{
    if (self && self->vtable)
        self->vtable->update(self, delta_time);
}

void object_transform(t_object *self, t_transform *transform)
{
    if (self && self->vtable)
        self->vtable->transform(self, transform);
}

void object_rotate(t_object *self, float x, float y, float z)
{
    if (self && self->vtable)
        self->vtable->rotate(self, x, y, z);
}

void object_translate(t_object *self, float x, float y, float z)
{
    if (self && self->vtable)
        self->vtable->translate(self, x, y, z);
}

void object_scale(t_object *self, float x, float y, float z)
{
    if (self && self->vtable)
        self->vtable->scale(self, x, y, z);
}

bool object_is_visible(t_object *self)
{
    if (self && self->vtable)
        return self->vtable->is_visible(self);
    return false;
}

void object_set_visible(t_object *self, bool visible)
{
    if (self && self->vtable)
        self->vtable->set_visible(self, visible);
}

void object_set_color(t_object *self, int color)
{
    if (self && self->vtable)
        self->vtable->set_color(self, color);
}

void object_set_custom_function(t_object *self, void (*func)(t_object *, void *), void *data)
{
    if (self && self->vtable)
        self->vtable->set_custom_function(self, func, data);
}

// Drawing utilities
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

// All object_create_* and object_destroy implementations should be here

// Transform utilities
t_transform transform_identity(void)
{
    t_transform transform = {0};

    // Identity matrix
    for (int i = 0; i < 4; i++)
    {
        transform.matrix[i][i] = 1.0f;
    }

    transform.scale = (t_point3d){1.0f, 1.0f, 1.0f};

    return transform;
}

void transform_multiply(t_transform *result, t_transform *a, t_transform *b)
{
    if (!result || !a || !b)
        return;

    // Simple matrix multiplication for 4x4 matrices
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result->matrix[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                result->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
            }
        }
    }

    // Combine position, rotation, and scale
    result->position.x = a->position.x + b->position.x;
    result->position.y = a->position.y + b->position.y;
    result->position.z = a->position.z + b->position.z;

    result->rotation.x = a->rotation.x + b->rotation.x;
    result->rotation.y = a->rotation.y + b->rotation.y;
    result->rotation.z = a->rotation.z + b->rotation.z;

    result->scale.x = a->scale.x * b->scale.x;
    result->scale.y = a->scale.y * b->scale.y;
    result->scale.z = a->scale.z * b->scale.z;
}

t_point3d transform_point(t_transform *transform, t_point3d point)
{
    if (!transform)
        return point;

    // Apply scale
    point.x *= transform->scale.x;
    point.y *= transform->scale.y;
    point.z *= transform->scale.z;

    // Apply rotation (simplified - would need proper matrix multiplication)
    // For now, just apply translation
    point.x += transform->position.x;
    point.y += transform->position.y;
    point.z += transform->position.z;

    return point;
}

t_point3d project_3d_to_2d(t_point3d point, float fov, float aspect, float near, float far)
{
    // Simple perspective projection
    t_point3d result;
    float z = point.z + 5.0f; // Move away from camera

    if (z <= 0.1f)
        z = 0.1f;

    result.x = (point.x * 500.0f) / z + 400.0f; // Center on screen
    result.y = (point.y * 500.0f) / z + 300.0f;
    result.z = point.z;

    return result;
}

// Shape creation helpers - these are the missing functions
t_object *object_create_point(float x, float y, float z)
{
    t_object *obj = object_new(OBJ_POINT);
    if (!obj)
        return NULL;

    obj->vertices = malloc(sizeof(t_point3d));
    if (!obj->vertices)
    {
        object_destroy(obj);
        return NULL;
    }
    obj->vertices[0] = (t_point3d){x, y, z};
    obj->vertex_count = 1;

    return obj;
}

t_object *object_create_line(t_point3d start, t_point3d end)
{
    t_object *obj = object_new(OBJ_LINE);
    if (!obj)
        return NULL;

    obj->vertices = malloc(sizeof(t_point3d) * 2);
    if (!obj->vertices)
    {
        object_destroy(obj);
        return NULL;
    }
    obj->vertices[0] = start;
    obj->vertices[1] = end;
    obj->vertex_count = 2;

    return obj;
}

t_object *object_create_circle(float radius, int segments)
{
    (void)segments; // Parameter not used in current implementation
    t_object *obj = object_new(OBJ_CIRCLE);
    if (!obj)
        return NULL;

    obj->radius = radius;
    return obj;
}

t_object *object_create_rectangle(float width, float height)
{
    t_object *obj = object_new(OBJ_RECTANGLE);
    if (!obj)
        return NULL;

    obj->width = width;
    obj->height = height;

    return obj;
}
return point;
}

t_point3d project_3d_to_2d(t_point3d point, float fov, float aspect, float near, float far)
{
    // Simple perspective projection
    t_point3d result;
    float z = point.z + 5.0f; // Move away from camera

    if (z <= 0.1f)
        z = 0.1f;

    result.x = (point.x * 500.0f) / z + 400.0f; // Center on screen
    result.y = (point.y * 500.0f) / z + 300.0f;
    result.z = point.z;

    return result;
}
