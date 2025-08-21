# Vector Data Structure

## Overview

A vector is a dynamic array that can grow and shrink at runtime, unlike static arrays. It automatically manages memory allocation and provides efficient access to elements by index.

## Key Features

- **Dynamic sizing**: Automatically resizes when capacity is exceeded
- **Efficient access**: O(1) random access to elements by index
- **Memory management**: Handles allocation and deallocation internally
- **Type generic**: Stores void pointers, can hold any data type

## Structure Definition

```c
typedef struct s_vector
{
    void    **data;     // Array of void pointers to elements
    size_t  size;       // Current number of elements
    size_t  capacity;   // Maximum number of elements before resize
}               t_vector;
```

## Constants

- `VECTOR_INITIAL_CAPACITY`: 4 - Initial capacity when creating a vector
- `VECTOR_GROWTH_FACTOR`: 2 - Multiplier for capacity when resizing

## Core Functions

### Creation and Destruction

- `t_vector *ft_vector_create(void)`: Creates a new empty vector
- `void ft_vector_destroy(t_vector *vector)`: Frees the vector and its data array

### Element Access

- `void *ft_vector_get(t_vector *vector, size_t index)`: Gets element at index
- `bool ft_vector_set(t_vector *vector, size_t index, void *element)`: Sets element at index

### Adding Elements

- `bool ft_vector_add_back(t_vector *vector, void *element)`: Adds element to the end
- `bool ft_vector_insert(t_vector *vector, size_t index, void *element)`: Inserts element at index

### Removing Elements

- `void *ft_vector_pop_back(t_vector *vector)`: Removes and returns last element
- `void *ft_vector_remove(t_vector *vector, size_t index)`: Removes and returns element at index

### Utility Functions

- `size_t ft_vector_size(t_vector *vector)`: Returns current number of elements
- `size_t ft_vector_capacity(t_vector *vector)`: Returns current capacity
- `bool ft_vector_is_empty(t_vector *vector)`: Checks if vector is empty
- `void ft_vector_clear(t_vector *vector)`: Removes all elements (sets size to 0)

### Advanced Functions

- `bool ft_vector_resize(t_vector *vector, size_t new_capacity)`: Manually resize capacity
- `void ft_vector_print_addresses(t_vector *vector)`: Prints memory addresses of elements

## Time Complexity

| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Access (get/set) | O(1) | Direct array access |
| Add back | O(1) amortized | May trigger resize |
| Pop back | O(1) | Simple decrement |
| Insert | O(n) | Requires shifting elements |
| Remove | O(n) | Requires shifting elements |
| Resize | O(n) | Copies all elements |

## Memory Management

- **Automatic growth**: When size reaches capacity, the vector automatically doubles its capacity
- **No automatic shrinking**: The vector doesn't automatically reduce capacity when elements are removed
- **Manual resize**: Use `ft_vector_resize()` to manually adjust capacity
- **Element ownership**: The vector stores pointers but doesn't manage the memory of the pointed-to objects

## Usage Example

```c
#include "ft_vector.h"

int main(void)
{
    t_vector *vec;
    int *num1, *num2, *num3;
    
    // Create vector
    vec = ft_vector_create();
    if (!vec)
        return (1);
    
    // Allocate some integers
    num1 = malloc(sizeof(int)); *num1 = 42;
    num2 = malloc(sizeof(int)); *num2 = 24;
    num3 = malloc(sizeof(int)); *num3 = 84;
    
    // Add elements
    ft_vector_add_back(vec, num1);
    ft_vector_add_back(vec, num2);
    ft_vector_insert(vec, 1, num3); // Insert at index 1
    
    // Access elements
    int *retrieved = (int *)ft_vector_get(vec, 0);
    printf("First element: %d\n", *retrieved);
    
    // Print vector info
    printf("Size: %zu, Capacity: %zu\n", 
           ft_vector_size(vec), ft_vector_capacity(vec));
    
    // Remove element
    int *removed = (int *)ft_vector_pop_back(vec);
    free(removed);
    
    // Clean up (remember to free the elements first)
    while (!ft_vector_is_empty(vec))
    {
        int *elem = (int *)ft_vector_pop_back(vec);
        free(elem);
    }
    ft_vector_destroy(vec);
    
    return (0);
}
```

## Important Notes

1. **Null Safety**: All functions check for null pointers and handle them gracefully
2. **Index Bounds**: Functions that take an index parameter check bounds before access
3. **Memory Responsibility**: The vector doesn't free the objects pointed to by the elements
4. **Return Values**: Functions return appropriate success/failure indicators
5. **Element Storage**: Only stores pointers, not the actual objects
6. **Capacity vs Size**: Capacity is allocated space, size is actual number of elements

## Error Handling

- Functions return `false` or `NULL` on failure
- Common failure cases:
  - Null vector pointer
  - Index out of bounds
  - Memory allocation failure
  - Invalid parameters (e.g., null content for set operations)

## Performance Considerations

- **Amortized O(1) insertion**: Adding elements is very fast due to capacity doubling
- **Memory overhead**: May use up to 2x the required memory due to capacity management
- **Cache locality**: Elements are stored contiguously for better cache performance
- **Pointer indirection**: One level of indirection when accessing elements
