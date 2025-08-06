/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:10:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 12:42:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "mlx.h"

//mlx_destroy_display was one that once not called cause the leaks still reachable
void	fdf_destroy_contents(t_app *fdf)
{
	// Clean up systems
	transition_cleanup();
	cleanup_z_perspective_control();
	dynamic_background_cleanup();
	dance_system_cleanup();
	object_effects_cleanup();
	texture_system_cleanup();
	
	free(fdf->points);
	free(fdf->color);
	free(fdf->transformed_points);
	free(fdf->edges);
	mlx_destroy_image(fdf->mlx, fdf->image);
	mlx_destroy_window(fdf->mlx, fdf->window);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
}
