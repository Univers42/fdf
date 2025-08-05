/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:42:54 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/06 01:46:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mlx.h"
#include <X11/X.h>
#include "libft/libft.h"

static inline void	init_transformation_stack(t_app *fdf)
{
	t_projection_ctl	*projection;

	fdf->transformation_stack.dirty[M_PROJECTION] = true;
	projection = &fdf->transformation_stack.projection;
	transformation_stack_origin(&fdf->transformation_stack,
		-((float)fdf->width / 2), -((float)fdf->height / 2),
		-(float)(fdf->min_z + fdf->max_z) / 2.0f);
	transformation_stack_isometric(&fdf->transformation_stack);
	make_projection_ctl(projection, (float) fdf->width, (float) fdf->height,
		(float)(fdf->max_z - fdf->min_z));
	transformation_stack_translate(&fdf->transformation_stack, 0, 0,
		-projection->box[2] / 2.0f);
	transformation_stack_update(&fdf->transformation_stack);
	center_model(&fdf->transformation_stack, fdf->width, fdf->height,
		(float)(fdf->max_z - fdf->min_z));
}

static inline bool	init_after_parsing(t_app *fdf)
{
	bool	ok;
	size_t	n;

	if (fdf->width <= 0 || fdf->height <= 0)
		return (printf("Error: Invalid map dimensions (%d x %d)\n",
				fdf->width, fdf->height), false);
	ok = false;
	make_transformation_stack(&fdf->transformation_stack);
	init_transformation_stack(fdf);
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
		ok = true;
	}
	else
		printf("Error: Memory allocation failed\n");
	return (ok);
}

bool	make_fdf(t_app *fdf, char *filename)
{
	bool	ok;

	ok = false;
	ft_memset(fdf, 0, sizeof(t_app));
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
