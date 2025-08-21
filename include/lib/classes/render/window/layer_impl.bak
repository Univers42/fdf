#include "window.h"

t_layer *layer_new(int z_index)
{
    t_layer *layer = malloc(sizeof(t_layer));
    if (!layer)
        return NULL;

    layer->z_index = z_index;
    layer->objects = malloc(sizeof(t_object *) * 10);
    if (!layer->objects)
    {
        free(layer);
        return NULL;
    }
    layer->object_count = 0;
    layer->object_capacity = 10;
    layer->next = NULL;

    return layer;
}

void layer_destroy(t_layer *layer)
{
    if (!layer)
        return;

    if (layer->objects)
        free(layer->objects);
    free(layer);
}

void layer_add_object(t_layer *layer, t_object *obj)
{
    if (!layer || !obj)
        return;

    if (layer->object_count >= layer->object_capacity)
    {
        layer->object_capacity *= 2;
        t_object **new_objects = realloc(layer->objects,
                                         sizeof(t_object *) * layer->object_capacity);
        if (!new_objects)
            return;
        layer->objects = new_objects;
    }

    layer->objects[layer->object_count++] = obj;
}

void layer_remove_object(t_layer *layer, t_object *obj)
{
    if (!layer || !obj)
        return;

    for (size_t i = 0; i < layer->object_count; i++)
    {
        if (layer->objects[i] == obj)
        {
            // Shift remaining objects
            for (size_t j = i; j < layer->object_count - 1; j++)
            {
                layer->objects[j] = layer->objects[j + 1];
            }
            layer->object_count--;
            break;
        }
    }
}
