/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:06:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 16:09:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

void	cleanup_z_perspective_control(void)
{
	t_z_perspective	ctrl;

	ctrl = gzperspective(NULL);
	if (ctrl.original_z_values)
	{
		free(ctrl.original_z_values);
		ctrl.original_z_values = NULL;
	}
	ctrl.initialized = false;
	ctrl.scale_factor = 1.0f;
	gzperspective(&ctrl);
}

void	color_snapshot_capture(t_app *fdf)
{
	int	total;
	int	bytes;

	if (!fdf || !fdf->color)
		return ;
	total = fdf->width * fdf->height;
	if (total <= 0)
		return ;
	if (fdf->snapshot)
		free(fdf->snapshot);
	bytes = (int)(sizeof(uint32_t) * total);
	fdf->snapshot = (uint32_t *)malloc(bytes);
	if (!fdf->snapshot)
		return ;
	ft_memcpy(fdf->snapshot, fdf->color, (size_t)bytes);
	fdf->color_count = total;
}

void	color_snapshot_restore(t_app *fdf)
{
	int	total;
	int	bytes;

	if (!fdf || !fdf->color || !fdf->snapshot)
		return ;
	total = fdf->width * fdf->height;
	if (total != fdf->color_count || total <= 0)
		return ;
	bytes = (int)(sizeof(uint32_t) * total);
	ft_memcpy(fdf->color, fdf->snapshot, (size_t)bytes);
}
