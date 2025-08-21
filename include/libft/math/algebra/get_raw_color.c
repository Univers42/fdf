/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 03:24:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:41:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint8_t	xtr_r(int c)
{
	return ((uint8_t)((c >> 16) & 0xFF));
}

uint8_t	xtr_g(int c)
{
	return ((uint8_t)((c >> 8) & 0xFF));
}

uint8_t	xtr_b(int c)
{
	return ((uint8_t)(c & 0xFF));
}
