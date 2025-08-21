# Doubly Linked List Data Structure

## Overview

A doubly linked list is a linear data structure where each node contains data and two pointers: one pointing to the next node and another pointing to the previous node. This allows for efficient bidirectional traversal.

## Key Features

- **Bidirectional traversal**: Can traverse forward and backward
- **Dynamic sizing**: No fixed size limit (memory permitting)
- **Efficient insertion/deletion**: O(1) at both ends
- **Type generic**: Stores void pointers, can hold any data type
- **Memory efficient**: Only allocates memory for actual elements

## Structure Definition

```c
typedef struct s_dll_node
{
    void                *data;
    struct s_dll_node   *next;  // Points to next node
    struct s_dll_node   *prev;  // Points to previous node
}                       t_dll_node;

typedef struct s_doubly_list
{
    t_dll_node  *head;  // Points to first node
    t_dll_node  *tail;  // Points to last node
    size_t      size;   // Current number of elements
}               t_doubly_list;
```

## Core Functions

### Creation and Destruction

- `t_doubly_list *ft_dll_create(void)`: Creates a new empty list
- `void ft_dll_destroy(t_doubly_list *list)`: Frees the list and all nodes

### Adding Elements

- `bool ft_dll_push_front(t_doubly_list *list, void *data)`: Adds element at front
- `bool ft_dll_push_back(t_doubly_list *list, void *data)`: Adds element at back
- `bool ft_dll_insert(t_doubly_list *list, size_t index, void *data)`: Inserts at index

### Removing Elements

- `void *ft_dll_pop_front(t_doubly_list *list)`: Removes and returns front element
- `void *ft_dll_pop_back(t_doubly_list *list)`: Removes and returns back element
- `void *ft_dll_remove(t_doubly_list *list, size_t index)`: Removes element at index
- `bool ft_dll_remove_data(t_doubly_list *list, void *data)`: Removes first occurrence

### Access Functions

- `void *ft_dll_front(t_doubly_list *list)`: Peeks at front element
- `void *ft_dll_back(t_doubly_list *list)`: Peeks at back element
- `void *ft_dll_get(t_doubly_list *list, size_t index)`: Gets element at index
- `bool ft_dll_set(t_doubly_list *list, size_t index, void *data)`: Sets element at index

### Utility Functions

- `size_t ft_dll_size(t_doubly_list *list)`: Returns number of elements
- `bool ft_dll_is_empty(t_doubly_list *list)`: Checks if list is empty
- `void ft_dll_clear(t_doubly_list *list)`: Removes all elements
- `void ft_dll_reverse(t_doubly_list *list)`: Reverses the list

### Search Functions

- `int ft_dll_find(t_doubly_list *list, void *data)`: Finds index of data (-1 if not found)
- `bool ft_dll_contains(t_doubly_list *list, void *data)`: Checks if data exists

### Debug Functions

- `void ft_dll_print_addresses(t_doubly_list *list)`: Prints forward
- `void ft_dll_print_reverse(t_doubly_list *list)`: Prints backward

## Time Complexity

| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Push/Pop Front | O(1) | Direct head access |
| Push/Pop Back | O(1) | Direct tail access |
| Insert/Remove at index | O(n) | May need traversal |
| Get/Set by index | O(n) | Optimized for closer end |
| Find/Contains | O(n) | Linear search |
| Size/IsEmpty | O(1) | Stored as member |
| Reverse | O(n) | Swaps all pointers |

## Memory Management

- **Dynamic allocation**: Each element is stored in a separate node
- **Automatic cleanup**: `ft_dll_destroy()` frees all nodes
- **Element ownership**: List doesn't manage memory of pointed-to objects
- **Memory overhead**: Each node requires two pointer fields

## Usage Example

```c
#include "ft_doubly_list.h"

int main(void)
{
    t_doubly_list *list;
    int *num1, *num2, *num3;
    
    // Create list
    list = ft_dll_create();
    if (!list)
        return (1);
    
    // Allocate some integers
    num1 = malloc(sizeof(int)); *num1 = 10;
    num2 = malloc(sizeof(int)); *num2 = 20;
    num3 = malloc(sizeof(int)); *num3 = 30;
    
    // Add elements
    ft_dll_push_back(list, num1);   // List: [10]
    ft_dll_push_front(list, num2);  // List: [20, 10]
    ft_dll_insert(list, 1, num3);   // List: [20, 30, 10]
    
    // Access elements
    printf("Front: %d\n", *(int *)ft_dll_front(list));     // 20
    printf("Back: %d\n", *(int *)ft_dll_back(list));       // 10
    printf("Index 1: %d\n", *(int *)ft_dll_get(list, 1));  // 30
    
    // Search
    int index = ft_dll_find(list, num3);
    printf("num3 found at index: %d\n", index);            // 1
    
    // Remove elements
    int *removed = (int *)ft_dll_pop_front(list);          // Returns 20
    printf("Removed: %d\n", *removed);
    
    // Print both directions
    ft_dll_print_addresses(list);
    ft_dll_print_reverse(list);
    
    // Reverse the list
    ft_dll_reverse(list);
    printf("After reverse:\n");
    ft_dll_print_addresses(list);
    
    // Clean up
    while (!ft_dll_is_empty(list))
    {
        int *elem = (int *)ft_dll_pop_front(list);
        free(elem);
    }
    free(removed);
    ft_dll_destroy(list);
    
    return (0);
}
```

## Advantages over Singly Linked Lists

1. **Bidirectional traversal**: Can move backward efficiently
2. **Efficient deletion**: Can delete a node with just the node pointer
3. **Better cache locality**: Previous pointer enables backward optimization
4. **Reverse operations**: Can implement reverse iterators easily

## Common Use Cases

1. **Undo/Redo functionality**: Navigate command history
2. **Browser history**: Forward and backward navigation
3. **Music players**: Previous/next track functionality
4. **Text editors**: Cursor movement and text manipulation
5. **LRU cache implementation**: Move items to front/back efficiently

## Performance Optimizations

- **Index access optimization**: Chooses forward/backward traversal based on which is closer
- **Head/tail pointers**: O(1) access to both ends
- **Size tracking**: Avoids traversal for size queries

## Important Notes

1. **Bidirectional links**: Both next and prev pointers must be maintained
2. **Null safety**: All functions handle null pointers gracefully
3. **Memory responsibility**: Caller must free the data pointed to by elements
4. **Index bounds**: Get/set functions check bounds before access
5. **Consistent state**: Internal pointers are always kept consistent

## Error Handling

- Functions return `false` or `NULL` on failure
- Common failure cases:
  - Null list pointer
  - Index out of bounds
  - Memory allocation failure
  - Operations on empty list
