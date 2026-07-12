/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_int.h"

t_viewport	*gviewport(void)
{
	static t_viewport	vp = {WIN_WIDTH, WIN_HEIGHT, 0, 0, 0};

	return (&vp);
}

/*
 * MiniLibX pins min = max size in the WM hints, which is what blocks
 * edge-drag resizing. Re-issue sane hints: anything from 320x240 up to
 * the framebuffer maximum.
 */
void	viewport_init(t_app *f)
{
	XSizeHints	hints;

	ft_memset(&hints, 0, sizeof(hints));
	hints.flags = PMinSize | PMaxSize;
	hints.min_width = 320;
	hints.min_height = 240;
	hints.max_width = WIN_WIDTH;
	hints.max_height = WIN_HEIGHT;
	XSetWMNormalHints(((t_xvar *)f->mlx)->display,
		((t_win_list *)f->window)->window, &hints);
}

int	viewport_query(t_app *f, t_win_attr *a)
{
	Window			root;
	int				xy[2];
	unsigned int	geo[4];

	if (!XGetGeometry(((t_xvar *)f->mlx)->display,
			((t_win_list *)f->window)->window, &root, &xy[0], &xy[1],
			&geo[0], &geo[1], &geo[2], &geo[3]))
		return (0);
	a->w = (int)geo[0];
	a->h = (int)geo[1];
	return (1);
}

/*
 * MiniLibX never dispatches ConfigureNotify, so the size is polled
 * (one X round-trip every 8th frame). Cheap scaling follows the drag
 * live; the baked buffers (sky, black-hole LUT) rebuild once the size
 * has settled for a dozen polls.
 */
void	viewport_poll(t_app *f)
{
	t_viewport		*vp;
	t_win_attr		a;

	vp = gviewport();
	if ((++vp->tick & 7) != 0)
		return ;
	if (!viewport_query(f, &a))
		return ;
	if (a.w != vp->w || a.h != vp->h)
	{
		vp->w = imin2(a.w, WIN_WIDTH);
		vp->h = imin2(a.h, WIN_HEIGHT);
		vp->settle = 0;
		f->needs_redraw = true;
	}
	else if (vp->settle <= 12 && ++vp->settle == 12)
	{
		sky_free();
		black_hole_free();
		f->needs_redraw = true;
	}
}

/* F11 cycles window presets: full screen -> two thirds -> half. */
void	viewport_preset_handler(t_app *f, int keycode, void *data)
{
	t_viewport	*vp;
	t_xvar		*x;
	int			sw;
	int			sh;

	(void)keycode;
	(void)data;
	vp = gviewport();
	x = (t_xvar *)f->mlx;
	sw = imin2(DisplayWidth(x->display, x->screen), WIN_WIDTH);
	sh = imin2(DisplayHeight(x->display, x->screen), WIN_HEIGHT);
	vp->preset = (vp->preset + 1) % 3;
	if (vp->preset == 1)
		XResizeWindow(x->display, ((t_win_list *)f->window)->window,
			sw * 2 / 3, sh * 2 / 3);
	else if (vp->preset == 2)
		XResizeWindow(x->display, ((t_win_list *)f->window)->window,
			sw / 2, sh / 2);
	else
		XResizeWindow(x->display, ((t_win_list *)f->window)->window, sw, sh);
	f->needs_redraw = true;
}
