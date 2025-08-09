/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_theme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:30:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:52:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"
#include "theme.h"

static inline void	set_idx(t_app *fdf, int idx) { set_palette_index(idx, fdf); }

void	palette_1_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 0); }
void	palette_2_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 1); }
void	palette_3_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 2); }
void	palette_4_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 3); }
void	palette_5_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 4); }
void	palette_6_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 5); }
void	palette_7_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 6); }
void	palette_8_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 7); }
void	palette_9_handler(t_app *fdf, int keycode, void *data) { (void)keycode; (void)data; set_idx(fdf, 8); }
