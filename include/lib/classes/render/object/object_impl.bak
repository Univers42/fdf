#include "object.h"
#include <string.h>

// Forward declaration for window functions that we need
void window_put_pixel(t_window *window, int x, int y, int color);
void window_draw_line_simple(t_window *window, int x0, int y0, int x1, int y1, int color);
void window_draw_circle_simple(t_window *window, int cx, int cy, int radius, int color);
void window_draw_rectangle_simple(t_window *window, int x, int y, int width, int height, int color);

// Object vtable implementation
static t_object *object_constructor(t_object_type type);
static void object_destructor(t_object *self);
static void object_draw_impl(t_object *self, t_window *window);
static void object_update_impl(t_object *self, float delta_time);
static void object_transform_impl(t_object *self, t_transform *transform);
static void object_rotate_impl(t_object *self, float x, float y, float z);
static void object_translate_impl(t_object *self, float x, float y, float z);
static void object_scale_impl(t_object *self, float x, float y, float z);
static bool object_is_visible_impl(t_object *self);
static void object_set_visible_impl(t_object *self, bool visible);
static void object_set_color_impl(t_object *self, int color);
static void object_set_custom_function_impl(t_object *self, void (*func)(t_object *, void *), void *data);

// Ensure the global vtable is properly defined and linked
t_object_vtable g_object_vtable = {
    .new = object_constructor,
    .destroy = object_destructor,
    .draw = object_draw_impl,
    .update = object_update_impl,
    .transform = object_transform_impl,
    .rotate = object_rotate_impl,
    .translate = object_translate_impl,
    .scale = object_scale_impl,
    .is_visible = object_is_visible_impl,
    .set_visible = object_set_visible_impl,
    .set_color = object_set_color_impl,
    .set_custom_function = object_set_custom_function_impl};

static t_object *object_constructor(t_object_type type)
{
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return NULL;

    memset(obj, 0, sizeof(t_object));
    obj->vtable = &g_object_vtable;
    obj->type = type;
    obj->transform = transform_identity();
    obj->color = 0xFFFFFF;
    obj->visible = true;
    obj->is_3d = false;

    return obj;
}

static void object_destructor(t_object *self)
{
    if (!self)
        return;

    if (self->vertices)
        free(self->vertices);
    if (self->indices)
        free(self->indices);

    free(self);
}

static void object_draw_impl(t_object *self, t_window *window)
{
    if (!self || !window || !self->visible)
        return;

    // Call custom draw function if available
    if (self->custom_draw)
    {
        self->custom_draw(self, window, self->user_data);
        return;
    }

    // Default drawing based on object type
    switch (self->type)
    {
    case OBJ_POINT:
        if (self->vertex_count > 0)
        {
            t_point3d point = transform_point(&self->transform, self->vertices[0]);
            if (self->is_3d)
            {
                point = project_3d_to_2d(point, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
            }
            window_put_pixel(window, (int)point.x, (int)point.y, self->color);
        }
        break;
    case OBJ_LINE:
        if (self->vertex_count >= 2)
        {
            t_point3d start = transform_point(&self->transform, self->vertices[0]);
            t_point3d end = transform_point(&self->transform, self->vertices[1]);
            if (self->is_3d)
            {
                start = project_3d_to_2d(start, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
                end = project_3d_to_2d(end, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
            }
            window_draw_line_simple(window, (int)start.x, (int)start.y, (int)end.x, (int)end.y, self->color);
        }
        break;
    case OBJ_CIRCLE:
    {
        t_point3d center = transform_point(&self->transform, (t_point3d){0, 0, 0});
        if (self->is_3d)
        {
            center = project_3d_to_2d(center, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        }
        window_draw_circle_simple(window, (int)center.x, (int)center.y, (int)(self->radius * self->transform.scale.x), self->color);
    }
    break;
    case OBJ_RECTANGLE:
    {
        t_point3d pos = transform_point(&self->transform, (t_point3d){0, 0, 0});
        if (self->is_3d)
        {
            pos = project_3d_to_2d(pos, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        }
        window_draw_rectangle_simple(window, (int)pos.x, (int)pos.y,
                                     (int)(self->width * self->transform.scale.x),
                                     (int)(self->height * self->transform.scale.y), self->color);
    }
    break;
    case OBJ_TRIANGLE:
        if (self->vertex_count >= 3)
        {
            t_point3d v1 = transform_point(&self->transform, self->vertices[0]);
            t_point3d v2 = transform_point(&self->transform, self->vertices[1]);
            t_point3d v3 = transform_point(&self->transform, self->vertices[2]);
            if (self->is_3d)
            {
                v1 = project_3d_to_2d(v1, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);
                v2 = project_3d_to_2d(v2, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);
                v3 = project_3d_to_2d(v3, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);
            }
            draw_line(window, v1, v2, self->color);
            draw_line(window, v2, v3, self->color);
            draw_line(window, v3, v1, self->color);
        }
        break;
    case OBJ_POLYGON:
        // Draw lines between consecutive vertices
        for (size_t i = 0; i < self->vertex_count; i++)
        {
            size_t next = (i + 1) % self->vertex_count;
            t_point3d v1 = transform_point(&self->transform, self->vertices[i]);
            t_point3d v2 = transform_point(&self->transform, self->vertices[next]);
            if (self->is_3d)
            {
                v1 = project_3d_to_2d(v1, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);
                v2 = project_3d_to_2d(v2, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);
            }
            draw_line(window, v1, v2, self->color);
        }
        break;
    case OBJ_IMAGE:
        // Image rendering would require MLX image functions
        // Implementation depends on specific MLX image handling
        break;
    case OBJ_MESH_3D:
        // 3D mesh rendering using indices
        if (self->indices && self->vertex_count > 0)
        {
            for (size_t i = 0; i < self->index_count; i += 3)
            {
                if (i + 2 < self->index_count)
                {
                    t_point3d v1 = transform_point(&self->transform, self->vertices[self->indices[i]]);
                    t_point3d v2 = transform_point(&self->transform, self->vertices[self->indices[i + 1]]);
                    t_point3d v3 = transform_point(&self->transform, self->vertices[self->indices[i + 2]]);

                    v1 = project_3d_to_2d(v1, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);
                    v2 = project_3d_to_2d(v2, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);
                    v3 = project_3d_to_2d(v3, 45.0f, (float)window->width / window->height, 0.1f, 100.0f);

                    draw_line(window, v1, v2, self->color);
                    draw_line(window, v2, v3, self->color);
                    draw_line(window, v3, v1, self->color);
                }
            }
        }
        break;
    case OBJ_CUSTOM:
        // Custom objects should use custom_draw function
        break;
    }
}

static void object_update_impl(t_object *self, float delta_time)
{
    if (!self)
        return;

    if (self->custom_update)
        self->custom_update(self, delta_time, self->user_data);
}

static void object_transform_impl(t_object *self, t_transform *transform)
{
    if (!self || !transform)
        return;

    if (self->custom_transform)
        self->custom_transform(self, transform, self->user_data);
    else
        self->transform = *transform;
}

static void object_rotate_impl(t_object *self, float x, float y, float z)
{
    if (!self)
        return;

    self->transform.rotation.x += x;
    self->transform.rotation.y += y;
    self->transform.rotation.z += z;
}

static void object_translate_impl(t_object *self, float x, float y, float z)
{
    if (!self)
        return;

    self->transform.position.x += x;
    self->transform.position.y += y;
    self->transform.position.z += z;
}

static void object_scale_impl(t_object *self, float x, float y, float z)
{
    if (!self)
        return;

    self->transform.scale.x *= x;
    self->transform.scale.y *= y;
    self->transform.scale.z *= z;
}

static bool object_is_visible_impl(t_object *self)
{
    if (!self)
        return false;
    return self->visible;
}

static void object_set_visible_impl(t_object *self, bool visible)
{
    if (!self)
        return;
    self->visible = visible;
}

static void object_set_color_impl(t_object *self, int color)
{
    if (!self)
        return;
    self->color = color;
}

static void object_set_custom_function_impl(t_object *self, void (*func)(t_object *, void *), void *data)
{
    if (!self)
        return;
    self->custom_draw = func;
    self->user_data = data;
}

// Make sure transform_multiply is implemented
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
