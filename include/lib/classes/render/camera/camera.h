/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:13:51 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/28 21:13:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <stdlib.h>
# include <math.h>
# include "window.h"
# include "point.h"

# define NUM_POINTS 6

typedef enum e_camera_perspective
{
	CAMERA_ISOMETRIC,
	CAMERA_TOP,
	CAMERA_SIDE
}	t_camera_perspective;

typedef struct s_camera	t_camera;
typedef struct s_point	t_point;

typedef struct s_camera_vtable
{
	void				(*set_perspective)(t_camera *, t_camera_perspective);
	t_camera_perspective(*get_perspective)(t_camera *);
	t_vec2				(*project_point)(t_camera *, t_point *);
	void				(*move)(t_camera *, double, double);
	void				(*set_zoom)(t_camera *, double, double, double);
	void				(*zoom_by)(t_camera *, double, double, double);
	void				(*destroy)(t_camera *);
}	t_camera_vtable;

struct s_camera
{
	t_camera_perspective	perspective;
	double					offset_x;
	double					offset_y;
	double					zoom;
	t_camera_vtable			*vtable;
};

typedef struct s_app
{
	t_window	*win;
	t_camera	*camera;
	t_point		*points[NUM_POINTS];
}				t_app;

/* API */
t_camera				*camera_new(t_camera_perspective perspective);
void					camera_destroy(t_camera *camera);

/* Internal (vtable targets) */
void					camera_set_perspective(t_camera *self,
							t_camera_perspective perspective);
t_camera_perspective	camera_get_perspective(t_camera *self);
void					camera_move(t_camera *self, double dx, double dy);
void					camera_set_zoom(t_camera *self, double zoom,
							double cx, double cy);
void					camera_zoom_by(t_camera *self, double factor,
							double cx, double cy);
t_vec2					camera_project_point(t_camera *self, t_point *point);

#endif
