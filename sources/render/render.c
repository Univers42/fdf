/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 18:50:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <mlx.h>
#include <stdbool.h>
#include "fdf.h"
#include "libft.h"
#include "theme.h"
#include "bench.h"

/*
 * Matrix rows are hoisted and the multiply is inlined flat: one fused
 * loop over all points, no per-point function call, vectorizer-friendly.
 */
void	transform_points(t_app *f)
{
	const float	*m;
	float		*dp;
	int			i;
	int			x;
	int			y;

	m = f->trans_stack.combined;
	dp = (float *)f->transformed_points;
	i = 0;
	y = -1;
	while (++y < f->height)
	{
		x = -1;
		while (++x < f->width)
		{
			dp[0] = m[0] * x + m[1] * y + m[2] * f->points[i] + m[3];
			dp[1] = m[4] * x + m[5] * y + m[6] * f->points[i] + m[7];
			dp[2] = m[8] * x + m[9] * y + m[10] * f->points[i] + m[11];
			dp[3] = m[12] * x + m[13] * y + m[14] * f->points[i] + m[15];
			dp += 4;
			++i;
		}
	}
}

static void	scene_update(t_app *f)
{
	auto_rotate_update(f);
	trans_stack_update(&f->trans_stack);
	if (gcam()->active)
		camera_matrix(f, f->trans_stack.combined);
	transition_update(f);
	object_effects_update(f);
	dance_system_update(f);
	bench_lap(BS_ANIM);
	if (!transition_app_is_active(f))
		transform_points(f);
	black_hole_warp_points(f);
	bench_lap(BS_TRANSFORM);
	texture_system_update(f);
	update_shadow_effects(f);
	bench_lap(BS_FX);
}

static void	scene_compose(t_app *f)
{
	if (gcam()->active)
		sky_render(f);
	else if (dynamic_background_is_active())
		dynamic_background_update(f);
	else
	{
		generate_background(f, get_current_background_theme(f));
		generate_stars(f);
	}
	bench_lap(BS_BG);
	if (*gviewmode() != 0)
	{
		zbuf_clear();
		fdf_draw_surface(f);
	}
	if (*gviewmode() != 1)
		fdf_draw_lines(f);
	bench_lap(BS_LINES);
	particles_update(f);
	bench_lap(BS_PARTICLES);
}

static bool	scene_is_animating(t_app *f)
{
	return (f->auto_rotate || transition_app_is_active(f)
		|| dance_system_is_active() || object_effects_is_active()
		|| texture_system_is_active() || dynamic_background_is_active()
		|| particles_is_active() || is_trackball_active());
}

/*
 * Nothing moved and nothing is animating: keep the last frame, yield the
 * CPU. Input events flip needs_redraw, so reaction stays instant while
 * an idle scene costs ~0% CPU instead of a full redraw per loop tick.
 */
int	fdf_render(t_app *f)
{
	viewport_poll(f);
	if (!f->needs_redraw && !scene_is_animating(f) && !bench_active())
		return ((void)usleep(300), 0);
	f->needs_redraw = false;
	bench_begin();
	scene_update(f);
	scene_compose(f);
	if (mlx_put_image_to_window(f->mlx, f->window, f->image, 0, 0) == -1)
		return (-1);
	bench_lap(BS_PRESENT);
	bench_frame(f);
	return (0);
}
