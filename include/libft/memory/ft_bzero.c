/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:30:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
/**
 * The function erases the data in the specified number of bytes (`n`)
 * of memory starting at the location pointed to by `s`.
 * It achieves this by writing zeros (`0`) to that memory area.
 * 
 * @param s Pointer to the memory area to be zeroed.
 * @param n Number of bytes to set to zero.
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/**
 * Memory initialization in a low level app
 * We're working on a simple networkin library
 * or a low level application, where we mangage
 * network buffers. We need to zero out the contents
 * of a buffer to ensure that no leftover data (such
 * as old network data) remains in memory. 
 */

//void prepare_network_packet(char *buffer, size_t size)
//{
	/**
	 * int this functio we initialize the buffer;
	 * Then we initialize a defautl header within
	 * the buffer
	 * The first copy in this buffer would be of
	 * 5 bytes which will hold START
	 * Then we can add the data network to the 
	 * buffer
	 * later on: we'll observe that when initialize
	 * the buffer to 0, the compilator really understand
	 * '\0'
	 */
//	ft_bzero(buffer, size);
//	ft_memcpy(buffer, "START", 5);
//	ft_printf("Buffer prepare for sending: \n");
//	ft_printf("Byte-by-byte content of buffer : \n");
//	for (size_t i = 0; i < size; i++)
//	//this will print byte-byte  in hexadecimal format
//		ft_printf("%02x ", (unsigned char)*(buffer + i));
//	ft_printf("\n");
//}
//int main(void)
//{
//	size_t DEST_BUF;
//	char *packet_buffer;
//	
//	ft_printf("how many allocation you need for buffer :");
//	scanf("%ld", &DEST_BUF);
//	packet_buffer = (char *)malloc(DEST_BUF + 1);
//	if(!packet_buffer)
//		return 1;
//	prepare_network_packet(packet_buffer, DEST_BUF);
//	ft_printf("%s", packet_buffer);
//	free(packet_buffer);
//}