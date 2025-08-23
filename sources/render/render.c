/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 16:15:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <time.h>
#include <mlx.h>
#include <stdbool.h>
#include "fdf.h"
#include "libft.h"
#include "theme.h"

void	transform_points(t_app *f)
{
	int		i[2];
	float	sp[4];
	float	*dp;
	int		flat_index;

	i[0] = 0;
	while (i[0] < f->height)
	{
		i[1] = 0;
		while (i[1] < f->width)
		{
			flat_index = i[0] * f->width + i[1];
			sp[0] = (float) i[1];
			sp[1] = (float) i[0];
			sp[2] = f->points[flat_index];
			sp[3] = 1;
			dp = (float *) &f->transformed_points[flat_index];
			matrix4_dot_product(f->trans_stack.combined, sp, dp);
			++i[1];
		}
		++i[0];
	}
}

void	clear_screen(t_app *f)
{
	size_t		i;
	uint32_t	value;

	i = 0;
	value = get_background_color(f);
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		((uint32_t *)f->renderer.data)[i] = value;
		++i;
	}
}

int	fdf_render(t_app *f)
{
	auto_rotate_update(f);
	trans_stack_update(&f->trans_stack);
	transition_update(f);
	object_effects_update(f);
	dance_system_update(f);
	if (!transition_app_is_active(f))
		transform_points(f);
	texture_system_update(f);
	update_shadow_effects(f);
	if (dynamic_background_is_active())
		dynamic_background_update(f);
	else
	{
		generate_background(f, get_current_background_theme(f));
		generate_stars(f);
	}
	fdf_draw_lines(f);
	particles_update(f);
	if (mlx_put_image_to_window(f->mlx, f->window, f->image, 0, 0) == -1)
		return (-1);
	return (0);
}
