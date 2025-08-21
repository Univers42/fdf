/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:29:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
/**
 * learned how to deal with literals and why it 
 * causes segmentation fault if we don't deal with them
 */
/**
 * Set the memory location to a specific value
 * @param pointer starting address of memory to be filled
 * @param c value to be filled
 * @param number of bytes to be filled starting from ptr to be filled
 * @note
 * the pointer is a void pointer,
 * we can pass any type of pointer to this function
 */
// definition of the function
//void *ft_memset(void *ptr, int value, size_t num) {
//    unsigned char *byte_ptr = (unsigned char *)ptr;
//    unsigned char byte_value = (unsigned char)value;
//
//    // Set memory byte-by-byte until pointer is aligned to a larger size
//    while (num && ((uintptr_t)byte_ptr % sizeof(uint64_t)) != 0) {
//        *byte_ptr++ = byte_value;
//        num--;
//    }
//
//    // Use larger chunks (64 bits) for bulk memory operations
//    uint64_t wide_value = 0x0101010101010101 * byte_value;
//    uint64_t *wide_ptr = (uint64_t *)byte_ptr;
//    while (num >= sizeof(uint64_t)) {
//        *wide_ptr++ = wide_value;
//        num -= sizeof(uint64_t);
//    }
//
//    // Handle any remaining bytes
//    byte_ptr = (unsigned char *)wide_ptr;
//    while (num--) {
//        *byte_ptr++ = byte_value;
//    }
//
//    return ptr;
//}
/**
 * Fills the first `num` bytes of the memory area pointed to by `ptr`
 * with the constant byte `value`.
 * 
 * @param ptr A pointer to the memory area to fill.
 * @param value The value to set the bytes to (converted to unsigned char).
 * @param num The number of bytes to set.
 * @return A pointer to the memory area `ptr`.
 * 
 * @note The `value` is treated as an unsigned char, 
 * and it is replicated across the `num` bytes.
 */
void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*byte;

	byte = (unsigned char *)ptr;
	while (num--)
		*byte++ = (unsigned char)value;
	return (ptr);
}
//ft_memset
//int main(void)
//{
//	char *str = "hello, world";
//	char *cpy;
//	int arr[] = {10,5,4,6,14,154,4,5};
//	
//	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
//	ft_strlcpy(cpy, str, ft_strlen(str) + 1);
//	if(!cpy)
//		return 1;
//	
//	ft_printf("old string : %s\n", cpy);
//	puts("old array:");
//	for(int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
//		ft_printf("%d\t", arr[i]);
//	ft_printf("\n");
//	
//	ft_memset((char *)cpy,0,7);
//	ft_memset((int *)arr, 0, sizeof(arr));
//	
//	ft_printf("new cpying : %s\n", cpy);
//	puts("new array:");
//	for(int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
//		ft_printf("%d\t", arr[i]);
//	ft_printf("\n");
//
//	free(cpy);
//	return (0);
//}
