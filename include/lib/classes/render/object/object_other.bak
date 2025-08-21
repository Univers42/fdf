#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// Forward declarations to avoid circular dependencies
typedef struct s_object t_object;
typedef struct s_point3d t_point3d;
typedef struct s_transform t_transform;
typedef struct s_window t_window;
typedef struct s_object_vtable t_object_vtable;

// 3D Point structure
typedef struct s_point3d
{
    float x;
    float y;
    float z;
} t_point3d;

// Transform matrix structure
typedef struct s_transform
{
    float matrix[4][4];
    t_point3d position;
    t_point3d rotation;
    t_point3d scale;
} t_transform;

// Object types
typedef enum e_object_type
{
    OBJ_POINT,
    OBJ_LINE,
    OBJ_CIRCLE,
    OBJ_RECTANGLE,
    OBJ_TRIANGLE,
    OBJ_POLYGON,
    OBJ_IMAGE,
    OBJ_MESH_3D,
    OBJ_CUSTOM
} t_object_type;

// Object vtable - use pointers for all function parameters to avoid dependencies
typedef struct s_object_vtable
{
    t_object *(*new)(t_object_type type);
    void (*destroy)(t_object *self);
    void (*draw)(t_object *self, t_window *window);
    void (*update)(t_object *self, float delta_time);
    void (*transform)(t_object *self, t_transform *transform);
    void (*rotate)(t_object *self, float x, float y, float z);
    void (*translate)(t_object *self, float x, float y, float z);
    void (*scale)(t_object *self, float x, float y, float z);
    bool (*is_visible)(t_object *self);
    void (*set_visible)(t_object *self, bool visible);
    void (*set_color)(t_object *self, int color);
    void (*set_custom_function)(t_object *self, void (*func)(t_object *, void *), void *data);
} t_object_vtable;

// Object structure - use pointers to avoid embedding dependencies
struct s_object
{
    t_object_vtable *vtable;

    // Object properties
    t_object_type type;
    t_transform transform;
    int color;
    bool visible;
    bool is_3d;

    // Geometry data - use pointers
    t_point3d *vertices;
    size_t vertex_count;
    int *indices;
    size_t index_count;

    // Shape-specific data
    float radius; // for circles
    float width;  // for rectangles
    float height; // for rectangles

    // Image data (for image objects) - use pointers
    void *img_ptr;
    char *img_data;
    int img_width;
    int img_height;

    // Custom data and functions - use pointers
    void *user_data;
    void (*custom_draw)(t_object *self, t_window *window, void *data);
    void (*custom_update)(t_object *self, float delta_time, void *data);
    void (*custom_transform)(t_object *self, t_transform *transform, void *data);
};

// Global vtable instance - declared, not defined
extern t_object_vtable g_object_vtable;

// Public API
t_object *object_new(t_object_type type);
void object_destroy(t_object *self);
void object_draw(t_object *self, t_window *window);
void object_update(t_object *self, float delta_time);
void object_transform(t_object *self, t_transform *transform);
void object_rotate(t_object *self, float x, float y, float z);
void object_translate(t_object *self, float x, float y, float z);
void object_scale(t_object *self, float x, float y, float z);
bool object_is_visible(t_object *self);
void object_set_visible(t_object *self, bool visible);
void object_set_color(t_object *self, int color);
void object_set_custom_function(t_object *self, void (*func)(t_object *, void *), void *data);

// Shape creation helpers
t_object *object_create_point(float x, float y, float z);
t_object *object_create_line(t_point3d start, t_point3d end);
t_object *object_create_circle(float radius, int segments);
t_object *object_create_rectangle(float width, float height);
t_object *object_create_triangle(t_point3d p1, t_point3d p2, t_point3d p3);
t_object *object_create_image(char *file_path);

// Transform utilities
t_transform transform_identity(void);
void transform_multiply(t_transform *result, t_transform *a, t_transform *b);
t_point3d transform_point(t_transform *transform, t_point3d point);

// 3D to 2D projection
t_point3d project_3d_to_2d(t_point3d point, float fov, float aspect, float near, float far);

// Drawing utilities (forward declarations only - implementations need window.h)
void draw_line(t_window *window, t_point3d start, t_point3d end, int color);
void draw_circle(t_window *window, t_point3d center, float radius, int color);
void draw_rectangle(t_window *window, t_point3d pos, float width, float height, int color);

#endif
