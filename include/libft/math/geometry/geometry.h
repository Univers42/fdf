/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:05:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:40:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include <stdint.h>
# include <stdbool.h>
# include "pixel.h"
# include <math.h>

/* Provide aliases expected by point.h (reuse pixel.h types) */
typedef t_point2							t_vec2;
typedef t_fpoint3							t_position;
typedef t_point3							t_pos;
typedef struct s_sphere_data				t_sphere_data;
/* Callback for transformations */
typedef void								(*t_transform_callback)\
											(t_sphere_data *data);

/* Forward declaration for parser (map system) */
typedef struct s_parser						t_parser;

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define X 0
# define Y 1
# define Z 2

/* Spherical transformation data */
struct s_sphere_data
{
	t_fpoint2	*points;
	int			len;
	float		radius;
	t_fpoint3	limits;
	t_fpoint3	center;
	float		scale;
	bool		initialized;
};

/* Line types */
typedef struct s_line3
{
	t_point3	a;
	t_point3	b;
}	t_line3;

typedef struct s_line2
{
	t_point2	a;
	t_point2	b;
}	t_line2;

typedef struct s_rect2
{
	t_point2	min;
	t_point2	max;
}	t_rect2;

/* ...existing code... (add more geometry utilities below as needed) */

#endif