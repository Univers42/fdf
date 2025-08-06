/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 04:36:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <immintrin.h>
#include <stdint.h>
#include <time.h>
#include <mlx.h>
#include <stdbool.h>
#include "fdf.h"
#include "libft.h"
#include "colors_map.h"

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
			matrix4_dot_product(f->transformation_stack.combined, sp, dp);
			++i[1];
		}
		++i[0];
	}
}

void	clear_screen(t_app *f)
{
	size_t	i;
	uint32_t value;

	i = 0;
	value = get_background_color();
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		((uint32_t *)f->renderer.data)[i] = value;
		++i;
	}
}

void	auto_rotate_update(t_app *f);  // External declaration
void	transition_update(t_app *f);
void render_parallax_effect(t_app *fdf);
void animate_parallax_grid(void);
bool is_parallax_active(void);

int	fdf_render(t_app *f)
{
	auto_rotate_update(f);
	transformation_stack_update(&f->transformation_stack);
	
	// Update transition system
	transition_update(f);
	
	// Only transform points normally if transition system is not handling them
	if (!transition_is_active())
	{
		transform_points(f);
	}
	
	// Apply shadow effects before rendering
	update_shadow_effects(f);
	
	// FIRST: Generate themed background (replaces clear_screen)
	generate_background(f, get_current_background_theme());
	
	// SECOND: Add stars if enabled
	generate_stars(f);
	
	// THIRD: Draw parallax grid BEFORE model lines
	if (is_parallax_active())
	{
		animate_parallax_grid();
		render_parallax_effect(f);
	}
	
	// FOURTH: Draw the wireframe model with transparency preservation
	fdf_draw_lines(f);
	
	// FIFTH: Update and render particles LAST (on top of everything)
	particles_update(f);
	
	if (mlx_put_image_to_window(f->mlx, f->window, f->image, 0, 0) == -1)
		return (-1);
	return (0);
}