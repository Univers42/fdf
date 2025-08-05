/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#define TRACKBALLSIZE (0.8f)
#define RENORMCOUNT 97

// Vector operations
static void vzero(float *v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

static void vset(float *v, float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

static void vsub(const float *src1, const float *src2, float *dst)
{
	dst[0] = src1[0] - src2[0];
	dst[1] = src1[1] - src2[1];
	dst[2] = src1[2] - src2[2];
}

static void vcopy(const float *v1, float *v2)
{
	for (int i = 0; i < 3; i++)
		v2[i] = v1[i];
}

static void vcross(const float *v1, const float *v2, float *cross)
{
	float temp[3];
	
	temp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	temp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	temp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
	vcopy(temp, cross);
}

static float vlength(const float *v)
{
	return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static void vscale(float *v, float div)
{
	v[0] *= div;
	v[1] *= div;
	v[2] *= div;
}

static void vnormal(float *v)
{
	float len = vlength(v);
	if (len > 0.0f)
		vscale(v, 1.0f / len);
}

static float vdot(const float *v1, const float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

static void vadd(const float *src1, const float *src2, float *dst)
{
	dst[0] = src1[0] + src2[0];
	dst[1] = src1[1] + src2[1];
	dst[2] = src1[2] + src2[2];
}

// Project point onto trackball sphere
static float tb_project_to_sphere(float r, float x, float y)
{
	float d, t, z;
	
	d = sqrtf(x * x + y * y);
	if (d < r * 0.70710678118654752440f) // Inside sphere
		z = sqrtf(r * r - d * d);
	else // On hyperbola
	{
		t = r / 1.41421356237309504880f;
		z = t * t / d;
	}
	return z;
}

// Convert axis and angle to quaternion
static void axis_to_quat(float a[3], float phi, float q[4])
{
	vcopy(a, q);
	vnormal(q);
	vscale(q, sinf(phi / 2.0f));
	q[3] = cosf(phi / 2.0f);
}

// Normalize quaternion
static void normalize_quat(float q[4])
{
	float mag = sqrtf(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
	
	if (mag > 0.0f)
	{
		for (int i = 0; i < 4; i++)
			q[i] /= mag;
	}
}

// Main trackball rotation function
void trackball_rotate(float q[4], float p1x, float p1y, float p2x, float p2y)
{
	float a[3]; // Axis of rotation
	float phi;  // Rotation angle
	float p1[3], p2[3], d[3];
	float t;
	
	if (p1x == p2x && p1y == p2y)
	{
		// Zero rotation
		vzero(q);
		q[3] = 1.0f;
		return;
	}
	
	// Project points onto deformed sphere
	vset(p1, p1x, p1y, tb_project_to_sphere(TRACKBALLSIZE, p1x, p1y));
	vset(p2, p2x, p2y, tb_project_to_sphere(TRACKBALLSIZE, p2x, p2y));
	
	// Calculate axis of rotation (cross product)
	vcross(p2, p1, a);
	
	// Calculate rotation angle
	vsub(p1, p2, d);
	t = vlength(d) / (2.0f * TRACKBALLSIZE);
	
	// Clamp to avoid numerical issues
	if (t > 1.0f) t = 1.0f;
	if (t < -1.0f) t = -1.0f;
	phi = 2.0f * asinf(t);
	
	axis_to_quat(a, phi, q);
}

// Add two quaternions
void add_quats(float q1[4], float q2[4], float dest[4])
{
	static int count = 0;
	float t1[4], t2[4], t3[4];
	float tf[4];
	
	vcopy(q1, t1);
	vscale(t1, q2[3]);
	
	vcopy(q2, t2);
	vscale(t2, q1[3]);
	
	vcross(q2, q1, t3);
	vadd(t1, t2, tf);
	vadd(t3, tf, tf);
	tf[3] = q1[3] * q2[3] - vdot(q1, q2);
	
	dest[0] = tf[0];
	dest[1] = tf[1];
	dest[2] = tf[2];
	dest[3] = tf[3];
	
	if (++count > RENORMCOUNT)
	{
		count = 0;
		normalize_quat(dest);
	}
}

// Convert quaternion to 4x4 matrix
void quaternion_to_matrix4(float q[4], float m[16])
{
	float x = q[0], y = q[1], z = q[2], w = q[3];
	
	// Row 0
	m[0] = 1.0f - 2.0f * (y * y + z * z);
	m[1] = 2.0f * (x * y - z * w);
	m[2] = 2.0f * (x * z + y * w);
	m[3] = 0.0f;
	
	// Row 1
	m[4] = 2.0f * (x * y + z * w);
	m[5] = 1.0f - 2.0f * (x * x + z * z);
	m[6] = 2.0f * (y * z - x * w);
	m[7] = 0.0f;
	
	// Row 2
	m[8] = 2.0f * (x * z - y * w);
	m[9] = 2.0f * (y * z + x * w);
	m[10] = 1.0f - 2.0f * (x * x + y * y);
	m[11] = 0.0f;
	
	// Row 3
	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;
}
