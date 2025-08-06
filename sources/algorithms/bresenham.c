/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:43:21 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/06 11:48:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "libft/libft.h"
#include <math.h>

static void			bresenham_draw_loop(t_bresenham_ctx *ctx);
void				draw_line_bresenham(
							t_bresenham_state *bresenham,
							unsigned int *screen,
							int major_axis
							);

/**
 * draw_line_x_major - Draws a line where X is the major axis.
 * @bresenham: Pointer to the Bresenham state struct.
 * @screen: Pointer to the screen buffer.
 *
 * Example:
 *   draw_line_x_major(&bresenham, screen);
 */
void	draw_line_x_major(t_bresenham_state *bresenham, unsigned int *screen)
{
	draw_line_bresenham(bresenham, screen, 0);
}

/**
 * draw_line_y_major - Draws a line where Y is the major axis.
 * @bresenham: Pointer to the Bresenham state struct.
 * @screen: Pointer to the screen buffer.
 *
 * Example:
 *   draw_line_y_major(&bresenham, screen);
 */
void	draw_line_y_major(t_bresenham_state *bresenham, unsigned int *screen)
{
	draw_line_bresenham(bresenham, screen, 1);
}

/**
 * draw_line_bresenham - Setup and call the Bresenham loop.
 * @bresenham: Pointer to the Bresenham state struct.
 * @screen: Pointer to the screen buffer.
 * @major_axis: 0 for X-major, 1 for Y-major.
 *
 * This function prepares the state and calls the main loop.
 */
void	draw_line_bresenham(
	t_bresenham_state *bresenham,
	unsigned int *screen,
	int major_axis
)
{
	t_bresenham_ctx	ctx;

	init_color_delta(bresenham);
	bresenham->error_count = 2 * bresenham->delta[1 - major_axis]
		- bresenham->delta[major_axis];
	ctx.bresenham = bresenham;
	ctx.screen = screen;
	ctx.coord[0] = bresenham->p1[0];
	ctx.coord[1] = bresenham->p1[1];
	ctx.limit = bresenham->delta[major_axis];
	ctx.major_axis = major_axis;
	bresenham_draw_loop(&ctx);
}

/**
 * bresenham_draw_pixel - Draws a single pixel if inside bounds and allowed.
 * @ctx: Pointer to the Bresenham context struct.
 * @color: Color to draw.
 */
static inline void	bresenham_draw_pixel(t_bresenham_ctx *ctx, uint32_t color)
{
	if (ctx->coord[0] >= 0 && ctx->coord[0] < WIN_WIDTH
		&& ctx->coord[1] >= 0 && ctx->coord[1] < WIN_HEIGHT)
	{
		ctx->screen[ctx->coord[1] * WIN_WIDTH + ctx->coord[0]] = color;
	}
}

/**
 * bresenham_draw_loop - Main Bresenham loop, split for norminette.
 * @ctx: Pointer to the Bresenham context struct.
 */
static void	bresenham_draw_loop(t_bresenham_ctx *ctx)
{
	int			step;
	uint32_t	color;

	step = -1;
	color = ctx->bresenham->color1;
	while (++step <= ctx->limit)
	{
		bresenham_draw_pixel(ctx, color);
		ctx->coord[ctx->major_axis] += ctx->bresenham->step[ctx->major_axis];
		ctx->bresenham->error_count += \
		2 * ctx->bresenham->delta[1 - ctx->major_axis];
		if (ctx->bresenham->error_count > 0)
		{
			ctx->coord[1 - ctx->major_axis] += \
			ctx->bresenham->step[1 - ctx->major_axis];
			ctx->bresenham->error_count -= \
			2 * ctx->bresenham->delta[ctx->major_axis];
		}
		color = pack_color(ctx->bresenham, step);
	}
}
