/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:13:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:19:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	camera_destroy_method(t_camera *self)
{
	if (self != NULL)
		free(self);
}

t_camera_vtable	gcam_method(void)
{
	static bool				init = false;
	static t_camera_vtable	camera_method = NULL;

	if (!init)
	{
		camera_method = {
			.set_perspective = camera_set_perspective,
			.get_perspective = camera_get_perspective,
			.project_point = camera_project_point,
			.move = camera_move,
			.set_zoom = camera_set_zoom,
			.zoom_by = camera_zoom_by,
			.destroy = camera_destroy_method
		};
		init = true;
	}
	return (&camera_method);
}

t_camera	*camera_new(t_camera_perspective perspective)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (cam == NULL)
		return (NULL);
	cam->perspective = perspective;
	cam->offset_x = 0.0;
	cam->offset_y = 0.0;
	cam->zoom = 1.0;
	cam->vtable = &g_camera_vtable;
	return (cam);
}

void	camera_destroy(t_camera *camera)
{
	if (camera != NULL && camera->vtable != NULL)
		camera->vtable->destroy(camera);
}
