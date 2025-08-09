/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   electric_storm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:01:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_electric_storm_bg(uint32_t *b)
{
	float	t;

	t = gdynbg(NULL)->time_accumulator;
	storm_base(b);
	storm_bolts(b, t);
}
