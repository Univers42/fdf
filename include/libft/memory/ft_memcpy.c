/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:59:45 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
//#include "TDD/test.h"
/**
 * Copies `n` bytes from the memory area `src` to the memory area `dest`.
 * 
 * @param dest A pointer to the destination memory area.
 * @param src A pointer to the source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination memory area (`dest`).
 * 
 * @note The function does not check for overlapping memory areas; 
 * for overlapping areas, 
 *       `memmove` should be used instead.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src || n == 0)
		return (dest);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		++i;
	}
	return (dest);
}

//int main(void)
//{
//	char str[] = "hello world";
//	int arr[] = {211413,41,511,3,34,1324,31,3,153,1342};
//	int *ptr;
//	ptr = malloc(sizeof(int) * (sizeof(arr) / sizeof(arr[0])));
//	ft_memcpy((int *)ptr, (int *)arr, sizeof(arr));
//	ft_printf("array => ");
//	for(int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
//		ft_printf("%d\t", *(ptr + i));
//	ft_printf("\n");
//}
