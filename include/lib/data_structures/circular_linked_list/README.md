# Circular Linked List Data Structure

## Overview

A circular linked list is a variation of a linked list where the last node points back to the first node, forming a circle. This creates an endless loop structure that can be traversed indefinitely.

## Key Features

- **Circular structure**: Last node points to first node
- **No null pointers**: Every node has a valid next pointer
- **Dynamic sizing**: No fixed size limit (memory permitting)
- **Efficient rotation**: Easy to implement circular operations
- **Type generic**: Stores void pointers, can hold any data type

## Structure Definition

```c
typedef struct s_cl_node
{
    void                *data;
    struct s_cl_node    *next;  // Points to next node (last->next = first)
}                       t_cl_node;

typedef struct s_circular_list
{
    t_cl_node   *last;      // Points to last node (last->next is first)
    size_t      size;       // Current number of elements
}               t_circular_list;
```

## Core Functions

### Creation and Destruction

- `t_circular_list *ft_cl_create(void)`: Creates a new empty list
- `void ft_cl_destroy(t_circular_list *list)`: Frees the list and all nodes

### Adding Elements

- `bool ft_cl_push_front(t_circular_list *list, void *data)`: Adds element at front
- `bool ft_cl_push_back(t_circular_list *list, void *data)`: Adds element at back
- `bool ft_cl_insert(t_circular_list *list, size_t index, void *data)`: Inserts at index

### Removing Elements

- `void *ft_cl_pop_front(t_circular_list *list)`: Removes and returns front element
- `void *ft_cl_pop_back(t_circular_list *list)`: Removes and returns back element
- `void *ft_cl_remove(t_circular_list *list, size_t index)`: Removes element at index
- `bool ft_cl_remove_data(t_circular_list *list, void *data)`: Removes first occurrence

### Access Functions

- `void *ft_cl_front(t_circular_list *list)`: Peeks at front element
- `void *ft_cl_back(t_circular_list *list)`: Peeks at back element
- `void *ft_cl_get(t_circular_list *list, size_t index)`: Gets element at index
- `bool ft_cl_set(t_circular_list *list, size_t index, void *data)`: Sets element at index

### Utility Functions

- `size_t ft_cl_size(t_circular_list *list)`: Returns number of elements
- `bool ft_cl_is_empty(t_circular_list *list)`: Checks if list is empty
- `void ft_cl_clear(t_circular_list *list)`: Removes all elements
- `void ft_cl_rotate_forward(t_circular_list *list, size_t steps)`: Rotates forward
- `void ft_cl_rotate_backward(t_circular_list *list, size_t steps)`: Rotates backward

### Search Functions

- `int ft_cl_find(t_circular_list *list, void *data)`: Finds index of data (-1 if not found)
- `bool ft_cl_contains(t_circular_list *list, void *data)`: Checks if data exists

### Debug Functions

- `void ft_cl_print_addresses(t_circular_list *list)`: Prints one cycle
- `void ft_cl_print_n_times(t_circular_list *list, size_t n)`: Prints n cycles

## Time Complexity

| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Push/Pop Front | O(1) | Direct access via last->next |
| Push Back | O(1) | Direct access to last |
| Pop Back | O(n) | Need to find second-to-last |
| Insert/Remove | O(n) | May need traversal |
| Get/Set | O(n) | Linear traversal |
| Find/Contains | O(n) | Linear search |
| Rotate | O(k) | k = steps |

## Memory Management

- **Dynamic allocation**: Each element is stored in a separate node
- **Automatic cleanup**: `ft_cl_destroy()` frees all nodes
- **Element ownership**: List doesn't manage memory of pointed-to objects
- **Circular structure**: Must break cycle during cleanup

## Usage Example

```c
#include "ft_circular_list.h"

int main(void)
{
    t_circular_list *list;
    int *num1, *num2, *num3;
    
    // Create list
    list = ft_cl_create();
    if (!list)
        return (1);
    
    // Allocate some integers
    num1 = malloc(sizeof(int)); *num1 = 10;
    num2 = malloc(sizeof(int)); *num2 = 20;
    num3 = malloc(sizeof(int)); *num3 = 30;
    
    // Add elements
    ft_cl_push_back(list, num1);    // List: [10] -> cycles
    ft_cl_push_back(list, num2);    // List: [10, 20] -> cycles
    ft_cl_push_front(list, num3);   // List: [30, 10, 20] -> cycles
    
    // Access elements
    printf("Front: %d\n", *(int *)ft_cl_front(list));      // 30
    printf("Back: %d\n", *(int *)ft_cl_back(list));        // 20
    printf("Index 1: %d\n", *(int *)ft_cl_get(list, 1));   // 10
    
    // Rotation operations
    ft_cl_rotate_forward(list, 1);  // Now: [10, 20, 30] -> cycles
    printf("After forward rotation: %d\n", *(int *)ft_cl_front(list)); // 10
    
    ft_cl_rotate_backward(list, 2); // Now: [30, 10, 20] -> cycles
    printf("After backward rotation: %d\n", *(int *)ft_cl_front(list)); // 30
    
    // Print circular structure
    ft_cl_print_addresses(list);
    ft_cl_print_n_times(list, 2);   // Print 2 full cycles
    
    // Search
    int index = ft_cl_find(list, num2);
    printf("num2 found at index: %d\n", index);
    
    // Clean up
    while (!ft_cl_is_empty(list))
    {
        int *elem = (int *)ft_cl_pop_front(list);
        free(elem);
    }
    ft_cl_destroy(list);
    
    return (0);
}
```

## Advantages

1. **Endless traversal**: Can traverse indefinitely without null checks
2. **Efficient rotation**: Easy to implement round-robin algorithms
3. **No end nodes**: Every position is equivalent
4. **Memory efficiency**: No wasted null pointers

## Common Use Cases

1. **Round-robin scheduling**: Process scheduling algorithms
2. **Circular buffers**: Ring buffer implementation
3. **Game turns**: Player turn management
4. **Playlist looping**: Music/video playlist cycling
5. **Josephus problem**: Mathematical elimination problems

## Important Notes

1. **Infinite loops**: Be careful to avoid infinite traversal
2. **Single pointer**: Only need to store last pointer (first = last->next)
3. **Empty list handling**: Special case where last = NULL
4. **Rotation efficiency**: Forward rotation just moves the last pointer
5. **Memory responsibility**: Caller must free the data pointed to by elements

## Rotation Operations

- **Forward rotation**: Moves elements towards the front (last pointer advances)
- **Backward rotation**: Moves elements towards the back (last pointer retreats)
- **Optimization**: Rotation by n steps is equivalent to rotation by n % size steps

## Error Handling

- Functions return `false` or `NULL` on failure
- Common failure cases:
  - Null list pointer
  - Index out of bounds
  - Memory allocation failure
  - Operations on empty list

## Performance Considerations

- **Pop back**: O(n) operation as it requires finding second-to-last node
- **Rotation**: Very efficient due to circular structure
- **Cache locality**: Each node allocated separately (less cache-friendly than arrays)
- **Memory overhead**: One pointer per node
