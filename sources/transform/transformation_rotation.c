/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_rotation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 22:02:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/**
 * DIRTY: What is dirty flag, the dirty array, is a dirty flag indicating
 * that a specific transformation matrix has been modified and may need to
 * recomputation or reapplication in the rendering pipeline.
 * it helps optimize updates by signaling when the combined transformation
 * matrix should be recalculated, avoiding unnecessary computations
 * if unchanged
 * 
 * ROTATION: how rotation is done using matrices ?
 * Rotation is achieved by multiplying 3D points (in homogeneous coordinates
 * , e.g., [x,y,z,1] by the rotation matrix.) The process:
 * 
 * A point is transformed by matrix multiplication: new_point = matrix * point.
 * Multiple rotations are combined by multiplying their matrices
 * (e.g., combined = `Rx * Ry * Rz`)
 * The result is a rotated point in 3D space, preserving distances and angles
 * 
 * This allow efficient GPU/CPU application for rendering the rotated map.
 * The absolute approach ensure consistent orientation without drift.
 */

 
void	trans_stack_rotate_x(t_trans_stack *t, float dx)
{
	t->dirty[M_ROTATION_X] = true;
	t->rx += dx;
	identity_matrix4(t->matrices[M_ROTATION_X]);
	matrix4_rotate_x_abs(t->matrices[M_ROTATION_X], t->rx);
}

void	trans_stack_rotate_y(t_trans_stack *t, float dy)
{
	t->dirty[M_ROTATION_Y] = true;
	t->ry += dy;
	identity_matrix4(t->matrices[M_ROTATION_Y]);
	matrix4_rotate_y_abs(t->matrices[M_ROTATION_Y], t->ry);
}

/**
 * @brief Applies an absolute rotation around the Z-axis to the transformat:
 * 
 * This function marks the Z rotation matrix as `dirty` (needing recomputaiton),
 * accumulates the rotation deltat (dz) into the total z-rotation angle (rz),
 * resets the matrix to identity, and then applies an absolute rotation
 * by the accumulated angle. This ensure the matri represents the full
 * rotation from the origin, not an incremental change
 * 
 * @param t	Pointer to the transform stack structure
 * @param dz the delta angle (in radians) to add to the current Z-rotation
 */
void	trans_stack_rotate_z(t_trans_stack *t, float dz)
{
	t->dirty[M_ROTATION_Z] = true;
	t->rz += dz;
	identity_matrix4(t->matrices[M_ROTATION_Z]);
	matrix4_rotate_z_abs(t->matrices[M_ROTATION_Z], t->rz);
}
