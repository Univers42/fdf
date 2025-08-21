/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:51:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
//#include "TDD/test.h"
/**
 * Copies `n` bytes from the memory area `src` to the memory area `dest`,
 * ensuring that even if the memory areas overlap, the data is copied correctly.
 * 
 * @param dest A pointer to the destination memory area.
 * @param src A pointer to the source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination memory area (`dest`).
 * 
 * @note Unlike `memcpy`, `memmove` handles overlapping memory regions correctly
 *       by temporarily copying the data to a temporary buffer if needed.
 */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d == s || n == 0)
		return (dst);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dst);
}
//TODO : use backward and forward movement

//int main(void)
//{
//	char *str = "hello, world!";
//	int arr[] = {31223,1,541,564,515,44,545467,889,51,31,54};
//	int *ptr;
//	size_t arr_size = sizeof(arr)/sizeof(arr[0]);
//	ptr = malloc(sizeof(int)*arr_size);
//	if(!ptr)
//		return 1;
//	ft_memmove((int *)ptr, (int *)arr, sizeof(arr));
//	ft_printf("original array: \n");
//	for(size_t i = 0; i < arr_size; i++)
//		ft_printf("%d ", arr[i]);
//	ft_printf("\n");
//	for(size_t i = 0; i < arr_size; i++)
//		ft_printf("%d ", ptr[i]);
//	ft_printf("\n");
//	free(ptr);
//	return (0);
//}