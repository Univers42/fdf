/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:05:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 00:32:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if the given character is a digit (0-9).
 * 
 * @param c The character to check (represented as an int, 
 * typically from an unsigned char or EOF).
 * @return 1 if the character is a digit, 0 otherwise.
 */
int	ft_isdigit(int c)
{
	unsigned char	high_bits;
	unsigned char	low_bits;

	high_bits = c & 0xF0;
	low_bits = c & 0x0F;
	return ((high_bits == 0x30) && (low_bits <= 9));
}
