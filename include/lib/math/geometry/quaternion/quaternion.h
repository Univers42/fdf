/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:52:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:01:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H
# include <math.h>
# include "pixel.h"
# include "matrices.h"

# define TRACKBALLSIZE 0.5f
# define RENORMCOUNT 97

typedef struct s_slerp_interp
{
	float	theta_0;
	float	theta;
	float	sin_theta;
	float	sin_theta0;
	float	s0;
	float	s1;
}	t_slerp_interp;

typedef t_fpoint4	t_quat;
typedef t_fpoint3	t_mat;

/* Interpolation helper */
float	lerp(float a, float b, float t);

/* Quaternion init / creation */
void	quat_init(t_quat *q, t_fpoint4 p);
void	quat_from_axis_angle(t_quat *q, t_fpoint3 axis, float angle_rad);

/* Quaternion operations */
void	quat_normalize(t_quat *q);
void	quat_mult(t_quat *out, const t_quat *a, const t_quat *b);
void	quat_slerp(t_quat *out, const t_quat *a, const t_quat *b, float t);

/* Conversions */
void	quat_to_matrix(t_mat4 *out, const t_quat *q);
void	quaternion_to_matrix(float q[4], float m[3][3]);
void	build_rotmatrix(float m[4][4], float q[4]);
void	quaternion_to_matrix4(float q[4], float m[16]);

/* Trackball utilities */
float	tb_project_to_sphere(float r, t_fpoint2 p);
void	trackball_rotate(float q[4], t_fpoint2 p1, t_fpoint2 p2);
void	trackball(float q[4], t_fpoint2 p1, t_fpoint2 p2);
void	apply_trackball_matrix(float m[3][3], t_point *point);

/* Low-level raw quaternion helpers */
void	add_quats(float q1[4], float q2[4], float dest[4]);
void	axis_to_quat(float a[3], float phi, float q[4]);
void	normalize_quat(float q[4]);

/* Vector helpers */
void	vcopy(const float *v1, float *v2);
void	vscale(float *v, float div);
void	vnormal(float *v);
void	vset(float *v, float x, float y, float z);
void	vsub(const float *src1, const float *src2, float *dst);
void	vzero(float *v);
float	vlength(const float *v);
float	vdot(const float *v1, const float *v2);
void	vcross(const float *v1, const float *v2, float *cross);
void	vadd(const float *src1, const float *src2, float *dst);
void	build_rotmatrix(float m[4][4], float q[4]);
float	tb_project_to_sphere(float r, t_fpoint2 p);
void	quaternion_to_matrix4(float q[4], float m[16]);

#endif
