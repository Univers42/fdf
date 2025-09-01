/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_projection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/09/01 09:13:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"

/**
ISOMETRIC: in true isometric view, the three axes (X,Y,Z) should appear
equally foreshortened (scaled) in the 2D projection. This require specific
rotations
ANGLE: The key angle is derived from the geometry of a cube viewed
isometrically. The ortation around the X-axis is `arctan(1 / sqrt(2))`
which equals approximately 35.264 degrees.
in radians arctan(1 / sqrt(2) ~= 0.6154797) (rounded to floating point
precision)

The precision avoid distortion and aligns with standard 3D graphis
convention. if approximated (e.g., to 0.6) the axes wouldn't be
equally foreshortened, leading to a less accurate isometric view
for exactness it's often computed as atanf(1.0f / sqrtf(2.0f))
but here it's hardcoded for efficiency
*/
#define ISOMETRIC_ANGLE 0.6155f

/**
Sets up an isometric projection by applying rotations (deg(45)) around z axis
then fadjustment for isometric view. This creates a matrix that simulates
a 3D to 2D projection without perspective distortion
*/
void	trans_stack_isometric(t_trans_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	trans_stack_rview_z(t, M_PI_4);
	trans_stack_rview_x(t, M_PI_2);
	trans_stack_rview_x2(t, -ISOMETRIC_ANGLE);
	trans_stack_rotate_x(t, 0);
	trans_stack_rotate_y(t, 0);
	trans_stack_rotate_z(t, 0);
}

/**
sets up a parallel (orthographic) projection
by resetting rotations, resulting in a flat
non perspective view.
*/
void	trans_stack_parallel(t_trans_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	trans_stack_rview_z(t, 0);
	trans_stack_rview_x(t, 0);
	trans_stack_rview_x2(t, 0);
	trans_stack_rotate_x(t, 0);
	trans_stack_rotate_y(t, 0);
	trans_stack_rotate_z(t, 0);
}
