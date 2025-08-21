/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:42:54 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/21 15:01:42 by dlesieur         ###   ########.fr       */
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
		.max_frames = 60,
		.active = false,
		.current_shape = SHAPE_ORIGINAL,
		.target_shape = SHAPE_ORIGINAL,
		.original_positions = NULL,
		.initialized = false
	};
}

static inline bool	init_after_parsing(t_app *fdf)
{
	bool	ok;
	size_t	n;

	if (fdf->width <= 0 || fdf->height <= 0)
		return (printf("Error: Invalid map dimensions (%d x %d)\n",
				fdf->width, fdf->height), false);
	ok = false;
	make_trans_stack(&fdf->trans_stack);
	init_trans_stack(fdf);
	fdf->n_edges = (fdf->width - 1) * fdf->height
		+ (fdf->height - 1) * fdf->width;
	n = sizeof(int [fdf->n_edges][2]);
	fdf->edges = malloc(n);
	fdf->transformed_points = malloc(
			sizeof(t_point4[fdf->height * fdf->width]));
	if (fdf->edges != NULL && fdf->transformed_points != NULL)
	{
		fdf_init_edges(fdf);
		init_mlx_handlers(fdf);
		helper_state(&fdf->transition_state);
		ok = true;
	}
	else
		ft_printf("Error: Memory allocation failed\n");
	return (ok);
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
	bool	ok;

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
		if (parse_file(fdf, filename)
			&& fdf->window != NULL
			&& fdf->image != NULL
			&& fdf->renderer.data != NULL)
			ok = init_after_parsing(fdf);
	}
	return (ok);
}
