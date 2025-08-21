# Queue Data Structure

## Overview

A queue is a linear data structure that follows the First-In-First-Out (FIFO) principle. Elements are added at the rear (enqueue) and removed from the front (dequeue).

## Key Features

- **FIFO ordering**: First element added is the first to be removed
- **Efficient operations**: O(1) enqueue and dequeue operations
- **Dynamic sizing**: No fixed size limit (memory permitting)
- **Type generic**: Stores void pointers, can hold any data type

## Structure Definition

```c
typedef struct s_queue_node
{
    void                *data;
    struct s_queue_node *next;
}                       t_queue_node;

typedef struct s_queue
{
    t_queue_node    *front;    // Points to first element
    t_queue_node    *rear;     // Points to last element
    size_t          size;      // Current number of elements
}                   t_queue;
```

## Core Functions

### Creation and Destruction

- `t_queue *ft_queue_create(void)`: Creates a new empty queue
- `void ft_queue_destroy(t_queue *queue)`: Frees the queue and all nodes

### Adding and Removing Elements

- `bool ft_queue_enqueue(t_queue *queue, void *data)`: Adds element to rear
- `void *ft_queue_dequeue(t_queue *queue)`: Removes and returns front element

### Access Functions

- `void *ft_queue_front(t_queue *queue)`: Peeks at front element without removing
- `void *ft_queue_rear(t_queue *queue)`: Peeks at rear element without removing

### Utility Functions

- `size_t ft_queue_size(t_queue *queue)`: Returns number of elements
- `bool ft_queue_is_empty(t_queue *queue)`: Checks if queue is empty
- `void ft_queue_clear(t_queue *queue)`: Removes all elements

### Debug Functions

- `void ft_queue_print_addresses(t_queue *queue)`: Prints memory addresses

## Time Complexity

| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Enqueue | O(1) | Add to rear |
| Dequeue | O(1) | Remove from front |
| Front/Rear | O(1) | Direct pointer access |
| Size | O(1) | Stored as member |
| Is Empty | O(1) | Check size or pointers |
| Clear | O(n) | Must free all nodes |

## Memory Management

- **Dynamic allocation**: Each element is stored in a separate node
- **Automatic cleanup**: `ft_queue_destroy()` frees all nodes
- **Element ownership**: Queue doesn't manage memory of pointed-to objects
- **Memory efficiency**: Only allocates memory for actual elements

## Usage Example

```c
#include "ft_queue.h"

int main(void)
{
    t_queue *queue;
    int *num1, *num2, *num3;
    
    // Create queue
    queue = ft_queue_create();
    if (!queue)
        return (1);
    
    // Allocate some integers
    num1 = malloc(sizeof(int)); *num1 = 10;
    num2 = malloc(sizeof(int)); *num2 = 20;
    num3 = malloc(sizeof(int)); *num3 = 30;
    
    // Add elements (FIFO order)
    ft_queue_enqueue(queue, num1);  // Queue: [10]
    ft_queue_enqueue(queue, num2);  // Queue: [10, 20]
    ft_queue_enqueue(queue, num3);  // Queue: [10, 20, 30]
    
    // Check queue info
    printf("Size: %zu\n", ft_queue_size(queue));                    // 3
    printf("Front: %d\n", *(int *)ft_queue_front(queue));          // 10
    printf("Rear: %d\n", *(int *)ft_queue_rear(queue));            // 30
    
    // Remove elements (FIFO order)
    int *first = (int *)ft_queue_dequeue(queue);   // Returns 10
    int *second = (int *)ft_queue_dequeue(queue);  // Returns 20
    
    printf("Dequeued: %d, %d\n", *first, *second);
    printf("Remaining size: %zu\n", ft_queue_size(queue));         // 1
    
    // Clean up
    while (!ft_queue_is_empty(queue))
    {
        int *elem = (int *)ft_queue_dequeue(queue);
        free(elem);
    }
    free(first);
    free(second);
    ft_queue_destroy(queue);
    
    return (0);
}
```

## Common Use Cases

1. **Task scheduling**: Process tasks in order of arrival
2. **Breadth-first search**: Explore nodes level by level
3. **Buffer management**: Handle data streams
4. **Print queues**: Process print jobs in order
5. **Resource allocation**: Fair distribution of resources

## Important Notes

1. **FIFO guarantee**: Elements are always processed in insertion order
2. **Null safety**: All functions handle null pointers gracefully
3. **Memory responsibility**: Caller must free the data pointed to by elements
4. **Empty queue handling**: Operations on empty queue return NULL/false
5. **Two-pointer efficiency**: Maintains both front and rear pointers for O(1) operations

## Error Handling

- Functions return `false` or `NULL` on failure
- Common failure cases:
  - Null queue pointer
  - Memory allocation failure
  - Operations on empty queue
  - Invalid parameters

## Performance Considerations

- **Memory locality**: Each node allocated separately (less cache-friendly than arrays)
- **Memory overhead**: Each node requires additional pointer storage
- **No random access**: Must dequeue to access specific elements
- **Constant time operations**: All core operations are O(1)
