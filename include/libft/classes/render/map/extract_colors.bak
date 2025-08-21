/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:36:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 22:38:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int extract_red_component(unsigned int color)
{
    return ((color >> 16) & 0xFF);
}

int extract_green_component(unsigned int color)
{
    return ((color >> 8 & 0xFF));
}

int extract_blue_component(unsigned int color)
{
    return (color & 0xFF);
}