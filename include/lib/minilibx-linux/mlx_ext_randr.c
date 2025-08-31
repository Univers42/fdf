/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ext_randr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:33:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:33:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

#include	<unistd.h>
#include <X11/extensions/Xrandr.h>

/* global for independant extension */

RRMode	saved_mode = 0;

/**
 * @file mlx_ext_randr.c
 * @brief Provides fullscreen mode switching for MiniLibX windows using XRandR.
 *
 * This file contains functions to toggle fullscreen mode for a MiniLibX window
 * by interacting with the XRandR extension. It selects the best available screen
 * mode for fullscreen, saves the previous mode, and restores it when exiting fullscreen.
 *
 * The main function, mlx_ext_fullscreen, changes the window's display mode and
 * manages keyboard and pointer grabs as needed.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the window to be toggled.
 * @param fullscreen Non-zero to enable fullscreen, zero to restore previous mode.
 * @return Always returns 0.
 */
int			mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen)
{
  XWindowAttributes	watt;
  int			i;
  int			j;
  XRRScreenResources	*res;
  XRROutputInfo		*o_info;
  XRRCrtcInfo		*crtc;
  RRMode		mode_candidate;
  int			idx_output;
  int			idx_candidate;

  if (!XGetWindowAttributes(xvar->display, win->window, &watt))
    return (0);

  res = XRRGetScreenResources(xvar->display, xvar->root);
  o_info = NULL;
  idx_output = -1;
  i = res->noutput;
  while (i--)
    {
      o_info = XRRGetOutputInfo(xvar->display, res, res->outputs[i]);
      if (o_info->connection == RR_Connected)
	{
	  idx_output = i;
	  i = 0;
	}
      else
	XRRFreeOutputInfo(o_info);
    }
  if (!o_info)
    {
      XRRFreeScreenResources(res);
      return (0);
    }
  
  idx_candidate = -1;
  i = o_info->nmode;
  while (i--)
    {
      j = res->nmode;
      while (j--)
	if (res->modes[j].id == o_info->modes[i])
	  if (res->modes[j].width >= watt.width && res->modes[j].height >= watt.height &&
	      (idx_candidate == -1 || res->modes[idx_candidate].width > res->modes[j].width ||
	       res->modes[idx_candidate].height > res->modes[j].height) )
	    idx_candidate = i;
    }
  if (idx_candidate < 0)
    {
      XRRFreeOutputInfo(o_info);
      XRRFreeScreenResources(res);
      return (0);
    }
  if (!fullscreen && saved_mode == -1)
    idx_candidate = 0; /* if no clue, uses first mode, usually part of npreferred */
  mode_candidate = o_info->modes[idx_candidate];
  if (!fullscreen)
    mode_candidate = saved_mode;

  crtc = XRRGetCrtcInfo(xvar->display, res, o_info->crtc);
  saved_mode = crtc->mode;

  i = XRRSetCrtcConfig(xvar->display, res, o_info->crtc, CurrentTime, 0, 0, mode_candidate,
		       crtc->rotation, &res->outputs[idx_output], 1);
  if (fullscreen)
    printf("found mode : %d x %d\n Status %d\n", res->modes[idx_candidate].width, res->modes[idx_candidate].height, i);
  else
    printf("back previous mode\n");
  
  XMoveWindow(xvar->display, win->window, 0, 0);
  XMapRaised(xvar->display, win->window);

  if (fullscreen)
    {
      //      XGrabPointer(xvar->display, win->window, True, 0, GrabModeAsync, GrabModeAsync, win->window, 0L, CurrentTime);
      XGrabKeyboard(xvar->display, win->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
  else
    {
      XUngrabPointer(xvar->display, CurrentTime);
      XUngrabKeyboard(xvar->display, CurrentTime);
    }

  XSync(xvar->display, False);
  sleep(1);

  XRRFreeCrtcInfo(crtc);
  XRRFreeOutputInfo(o_info);
  XRRFreeScreenResources(res);
}
