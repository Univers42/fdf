/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:38:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 12:32:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/**
 * recreating ft_time enthropy
 */
// Method 1: Stack address entropy (most reliable)
// Extract meaningful bits from stack address
	// Stack addresses change between program runs
// keep lower 32 bits
//unsigned long	ft_time_stack(void)
//{
//	char			stack_var;
//	unsigned long	addr;
//
//	addr = (unsigned long)&stack_var;	
//	return (addr & 0xFFFFFFFF);
//}

// Method 2: Heap address entropy  
//unsigned long	ft_time_heap(void)
//{
//	void			*heap_ptr;;
//	unsigned long	addr;
//
//	heap_ptr = malloc(1);
//	addr = 0;
//	if (heap_ptr)
//	{
//		addr = (unsigned long)heap_ptr;
//		free(heap_ptr);
//		return (addr & 0xFFFFFFFF);
//	}
//	return (ft_time_stack());
//}

// Method 3: Multiple stack variables for more entropy
//unsigned long ft_time_multi_stack(void)
//{
//	char a, b, c, d;
//	unsigned long addr_a = (unsigned long)&a;
//	unsigned long addr_b = (unsigned long)&b;  
//	unsigned long addr_c = (unsigned long)&c;
//	unsigned long addr_d = (unsigned long)&d;
//	
//	// Combine multiple stack addresses
//	return (addr_a ^ (addr_b << 8) ^ (addr_c << 16) ^ (addr_d << 24));
//}

// Method 4: Function address entropy
//unsigned long	get_function_addr(void)
//{
//	return ((unsigned long)&get_function_addr);
//}

/**
Combine function addr with stack
*/
//unsigned long	ft_time_function(void)
//{
//	unsigned long	func_addr;
//	char			stack_var;
//	unsigned long	stack_addr;
//
//	fun_addr = get_function_addr();
//	stack_addr = (unsigned long)&stack_var;
//	return ((func_addr ^ stack_addr) & 0xFFFFFFFF);
//}

// Method 5: Counter-based with stack entropy
//Combine counter with current stack position
//unsigned long	ft_time_counter(void)
//{
//	static unsigned long	counter = 0;
//	char					stack_var;
//	unsigned long			stack_addr;
//
//	stack_addr = (unsigned long)&stack_var;
//	return ((++counter * 1000) + (stack_addr & 0xFFF));
//}

// Method 6: Recursive stack entropy (changes with each call)
//Combine current address value with recursive call,
// not returning the address itself
// Combine current address value with recursive call, not returning
//the addresss itself
//unsigned long	recursive_entropy(int depth)
//{
//	char			local_var;
//	unsigned long	entropy;
//
//	entropy = (unsigned long)&local_var;
//	if (depth <= 0)
//		return (entropy);
//	return (entropy ^ recursive_entropy(depth - 1));
//}

//unsigned long	ft_time_recursive(void)
//{
//	return (recursive_entropy(5) & 0xFFFFFFFF);
//}

// Main ft_time function - combines multiple entropy sources
/**
Combine multiple entropy sources
Stack entropy
Heap entropy (if malloc is allowed)
counter entropy
function address entropy
*/
unsigned long	ft_time(void)
{
	static unsigned long	counter = 0;
	unsigned long			entropy;
	void					*heap_ptr;
	char					stack_var;

	entropy = 0;
	entropy ^= (unsigned long)&stack_var;
	heap_ptr = malloc(sizeof(int));
	if (heap_ptr)
	{
		entropy ^= (unsigned long)heap_ptr;
		free(heap_ptr);
	}
	entropy ^= ++counter;
	entropy ^= (unsigned long)&ft_time;
	return (entropy & 0xFFFFFFFF);
}

// Simple version if malloc is not allowed
unsigned long	ft_time_simple(void)
{
	static unsigned long	counter = 0;
	unsigned long			stack_addr;
	char					stack_var;

	stack_addr = (unsigned long)&stack_var;
	return ((stack_addr ^ (++counter * 12345)) & 0xFFFFFFFF);
}

// Test all methods
//void test_entropy_methods(void)
//{
//    printf("=== Testing Entropy Methods (No System Calls) ===\n\n");
//    
//    printf("Stack entropy method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time_stack());
//    }
//    
//    printf("\nHeap entropy method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time_heap());
//    }
//    
//    printf("\nMulti-stack entropy method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time_multi_stack());
//    }
//    
//    printf("\nFunction entropy method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time_function());
//    }
//    
//    printf("\nCounter entropy method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time_counter());
//    }
//    
//    printf("\nRecursive entropy method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time_recursive());
//    }
//    
//    printf("\nCombined ft_time() method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time());
//    }
//    
//    printf("\nSimple ft_time() method:\n");
//    for (int i = 0; i < 3; i++) {
//        printf("  Call %d: %lu\n", i+1, ft_time_simple());
//    }
//}

// Demonstrate with RNG seeding
//void test_with_rng(void)
//{
//    printf("\n=== Testing with RNG ===\n");
//    
//    // Simulate seeding RNG with different entropy methods
//    printf("Different runs would produce different seeds:\n");
//    
//    printf("Run 1 seed: %lu\n", ft_time());
//    printf("Run 2 seed: %lu\n", ft_time());
//    printf("Run 3 seed: %lu\n", ft_time());
//    
//    printf("\nEach program execution will
// have different stack/heap layout,\n");
//    printf("giving different seeds automatically!\n");
//}

//int main(void)
//{
//    test_entropy_methods();
//    test_with_rng();
//    
//    printf("\n=== Recommendations ===\n");
//    printf("BEST for libft: ft_time_simple() - uses only basic operations\n");
//    printf("GOOD if malloc allowed: ft_time() - combines multiple sources\n");
//    printf("MINIMAL: ft_time_stack() - just stack address\n\n");
//    
//    printf("Usage in your code:\n");
//    printf("ft_srand(ft_time_simple(), RNG_LCG);\n\n");
//    
//    printf("Why this works:\n");
//    printf("- Stack addresses are different each program run\n");
//    printf("- Counter increments with each call\n");
//    printf("- No system calls needed!\n");
//    printf("- Creates different seeds automatically\n");
//    
//    return 0;
//}