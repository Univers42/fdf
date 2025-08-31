/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:22:10 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:22:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"
#include	<stdlib.h>

/**
 * @brief Initializes the MiniLibX library and returns a display context.
 *
 * This function sets up the connection to the X11 display, initializes
 * screen, root window, colormap, and color depth, and prepares internal
 * structures for window management and event handling. It also checks
 * for TrueColor visual support and shared memory capabilities.
 *
 * @return Pointer to the initialized MiniLibX display context (t_xvar),
 *         or NULL on failure.
 */
void	*mlx_init()
{
	t_xvar	*xvar;

	if (!(xvar = malloc(sizeof(*xvar))))
		return ((void*)0);
	if ((xvar->display = XOpenDisplay("")) == 0)
	{
		free(xvar);
		return ((void*)0);
	}
	xvar->screen = DefaultScreen(xvar->display);
	xvar->root = DefaultRootWindow(xvar->display);
	xvar->cmap = DefaultColormap(xvar->display,xvar->screen);
	xvar->depth = DefaultDepth(xvar->display,xvar->screen);
	if (mlx_int_get_visual(xvar)==-1)
	{
		printf(ERR_NO_TRUECOLOR);
		exit(1);
	}
	xvar->win_list = 0;
	xvar->loop_hook = 0;
	xvar->loop_param = (void *)0;
	xvar->do_flush = 1;
	xvar->wm_delete_window = XInternAtom (xvar->display, "WM_DELETE_WINDOW", False);
	xvar->wm_protocols = XInternAtom (xvar->display, "WM_PROTOCOLS", False);
	mlx_int_deal_shm(xvar);
	if (xvar->private_cmap)
		xvar->cmap = XCreateColormap(xvar->display,xvar->root,
				 xvar->visual,AllocNone);
	mlx_int_rgb_conversion(xvar);
	xvar->end_loop = 0;
	return (xvar);
}


/*
** pshm_format of -1 :	Not XYBitmap|XYPixmap|ZPixmap
** alpha libX need a check of the DISPLAY env var, or shm is allowed
** in remote Xserver connections.
*/
/**
 * @brief Checks and configures X11 shared memory support for MiniLibX.
 *
 * This function queries the X11 server for shared memory (XShm) support,
 * determines the appropriate pixmap format, and disables shared memory if
 * the display is remote or not compatible. It updates the display context
 * with shared memory usage flags and format information.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int		mlx_int_deal_shm(t_xvar *xvar)
{
	int		use_pshm;
	int		bidon;
	char	*dpy;
	char	buff[33];

	xvar->use_xshm = XShmQueryVersion(xvar->display,&bidon,&bidon,&(use_pshm));
	if (xvar->use_xshm && use_pshm)
		xvar->pshm_format = XShmPixmapFormat(xvar->display);
	else
		xvar->pshm_format = -1;
	gethostname(buff,32);
	dpy = getenv(ENV_DISPLAY);
	if (dpy && strlen(dpy) && *dpy!=':' && strncmp(dpy,buff,strlen(buff)) &&
			strncmp(dpy,LOCALHOST,strlen(LOCALHOST)) )
	{
		xvar->pshm_format = -1;
		xvar->use_xshm = 0;
	}
}

/**
 * @brief Calculates RGB bit shifts and lengths for TrueColor visuals.
 *
 * This function analyzes the red, green, and blue masks of the X11 visual
 * and determines the number of bits to shift and the length of each color
 * component. The results are stored in the decrgb array of the display context.
 * This is required for proper color conversion and pixel value calculation.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int		mlx_int_rgb_conversion(t_xvar *xvar)
{
	bzero(xvar->decrgb,sizeof(int)*6);
	while (!(xvar->visual->red_mask&1))
		{ xvar->visual->red_mask >>= 1; xvar->decrgb[0] ++; }
	while (xvar->visual->red_mask&1)
		{ xvar->visual->red_mask >>= 1; xvar->decrgb[1] ++; }
	while (!(xvar->visual->green_mask&1))
		{ xvar->visual->green_mask >>= 1; xvar->decrgb[2] ++; }
	while (xvar->visual->green_mask&1)
		{ xvar->visual->green_mask >>= 1; xvar->decrgb[3] ++; }
	while (!(xvar->visual->blue_mask&1))
		{ xvar->visual->blue_mask >>= 1; xvar->decrgb[4] ++; }
	while (xvar->visual->blue_mask&1)
		{ xvar->visual->blue_mask >>= 1; xvar->decrgb[5] ++; }
}
