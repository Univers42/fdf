/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:53:20 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 22:53:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mlx.h"
#include <X11/X.h>
#include "libft.h"
#include "bench.h"

static inline void	init_trans_stack(t_app *fdf)
{
	t_projection_ctl	*projection;

	fdf->trans_stack.dirty[M_PROJECTION] = true;
	projection = &fdf->trans_stack.projection;
	trans_stack_origin(&fdf->trans_stack,
		-((float)fdf->width / 2), -((float)fdf->height / 2),
		-(float)(fdf->min_z + fdf->max_z) / 2.0f);
	trans_stack_isometric(&fdf->trans_stack);
	make_projection_ctl(projection, (float) fdf->width, (float) fdf->height,
		(float)(fdf->max_z - fdf->min_z));
	trans_stack_translate(&fdf->trans_stack, 0, 0,
		-projection->box[2] / 2.0f);
	trans_stack_update(&fdf->trans_stack);
	center_model(&fdf->trans_stack, fdf->width, fdf->height,
		(float)(fdf->max_z - fdf->min_z));
}

void	helper_state(t_transition_state *state)
{
	*state = (t_transition_state){
		.frame = 0,
		.max_frames = TRANSITION_FRAMES,
		.active = false,
		.current_shape = SHAPE_ORIGINAL,
		.target_shape = SHAPE_ORIGINAL,
		.cloud_src = NULL,
		.cloud_dst = NULL
	};
}

static inline bool	init_after_parsing(t_app *fdf)
{
	if (fdf->width <= 0 || fdf->height <= 0)
		return (printf("Error: Invalid map dimensions (%d x %d)\n",
				fdf->width, fdf->height), false);
	make_trans_stack(&fdf->trans_stack);
	init_trans_stack(fdf);
	fdf->n_edges = (size_t)(fdf->width - 1) * fdf->height
		+ (size_t)(fdf->height - 1) * fdf->width;
	fdf->transformed_points = malloc(
			sizeof(t_fpoint4[fdf->height * fdf->width]));
	if (fdf->transformed_points == NULL)
		return (ft_printf("Error: Memory allocation failed\n"), false);
	init_mlx_handlers(fdf);
	helper_state(&fdf->transition_state);
	return (true);
}

static void	init_fdf_struct(t_app *fdf)
{
	ft_memset(fdf, 0, sizeof(t_app));
	fdf->current_bg_theme = 0;
	fdf->stars_enabled = 1;
	fdf->auto_rotate = false;
	fdf->shadow_mode = 0;
	fdf->has_color = false;
	fdf->input_state = INPUT_STATE_IDLE;
	fdf->drag_start[0] = 0;
	fdf->drag_start[1] = 0;
	ft_memset(&fdf->renderer, 0, sizeof(t_renderer));
	ft_memset(&fdf->bresenham_state, 0, sizeof(t_bresenham_state));
	ft_memset(&fdf->trans_stack, 0, sizeof(t_trans_stack));
	ft_memset(&fdf->palette_state, 0, sizeof(t_palette_state));
	ft_memset(&fdf->transition_state, 0, sizeof(t_transition_state));
}

bool	make_fdf(t_app *fdf, char *filename)
{
	bool		ok;
	uint64_t	t0;

	ok = false;
	init_fdf_struct(fdf);
	fdf->mlx = mlx_init();
	if (fdf->mlx != NULL)
	{
		fdf->window = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
		fdf->image = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
		ft_strlcpy(fdf->renderer.fps_string, "Fps:     ",
			sizeof(fdf->renderer.fps_string));
		fdf->renderer.data = mlx_get_data_addr(fdf->image, &fdf->renderer.bpp,
				&fdf->renderer.size_line, &fdf->renderer.is_big_endian);
		t0 = bench_now_ns();
		ok = parse_file(fdf, filename);
		bench_parse(bench_now_ns() - t0);
		ok = (ok && fdf->window != NULL && fdf->image != NULL
				&& fdf->renderer.data != NULL);
		if (ok)
			ok = init_after_parsing(fdf);
	}
	return (ok);
}
