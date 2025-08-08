/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   electric_storm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:01:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 20:18:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_electric_storm_bg(uint32_t *b)
{
	float	t;

	t = g_dynamic_bg.time_accumulator;
	storm_base(b);
	storm_bolts(b, t);
}
