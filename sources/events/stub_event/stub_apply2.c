/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_apply2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:53:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:53:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_chips_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_CHIPS);
}

void	apply_wave_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_WAVE);
}

void	apply_heart_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_HEART);
}

void	apply_cone_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_CONE);
}

void	apply_tube_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_TUBE);
}
