/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewmode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* 0 = wireframe, 1 = solid surface, 2 = solid + wire overlay. */
int	*gviewmode(void)
{
	static int	mode = 0;

	return (&mode);
}

void	viewmode_toggle_handler(t_app *fdf, int keycode, void *data)
{
	static const char	*names[3] = {"wireframe", "solid", "solid + wire"};
	int					*m;

	(void)keycode;
	(void)data;
	m = gviewmode();
	*m = (*m + 1) % 3;
	fdf->needs_redraw = true;
	ft_printf("View mode: %s\n", names[*m]);
}
