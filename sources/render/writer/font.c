/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 21:15:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include "libft/libft.h"
#include "fdf.h"

static inline uint8_t	*get_char(char c)
{
	if (c == 'F')
		return ((uint8_t *)FONT_CHAR_F);
	else if (c == 'p')
		return ((uint8_t *)FONT_CHAR_P);
	else if (c == 's')
		return ((uint8_t *)FONT_CHAR_S);
	else if (c == ':')
		return ((uint8_t *)FONT_CHAR_COLON);
	else if (c == '.')
		return ((uint8_t *)FONT_CHAR_PERIOD);
	else
		return ((uint8_t *)FONT_CHAR_SPACE);
}

uint8_t	*get_glyph(char c)
{
	if (c == '0')
		return ((uint8_t *)FONT_CHAR_0);
	else if (c == '1')
		return ((uint8_t *)FONT_CHAR_1);
	else if (c == '2')
		return ((uint8_t *)FONT_CHAR_2);
	else if (c == '3')
		return ((uint8_t *)FONT_CHAR_3);
	else if (c == '4')
		return ((uint8_t *)FONT_CHAR_4);
	else if (c == '5')
		return ((uint8_t *)FONT_CHAR_5);
	else if (c == '6')
		return ((uint8_t *)FONT_CHAR_6);
	else if (c == '7')
		return ((uint8_t *)FONT_CHAR_7);
	else if (c == '8')
		return ((uint8_t *)FONT_CHAR_8);
	else if (c == '9')
		return ((uint8_t *)FONT_CHAR_9);
	else
		return (get_char(c));
}
