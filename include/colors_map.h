/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:29:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 03:58:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_MAP_H
#define COLORS_MAP_H

#include <stdint.h>

typedef struct s_pack_color
{
	uint32_t	color;
	uint32_t	bg_color;
}				t_pack_color;


void		set_background_theme(int theme);


#endif
