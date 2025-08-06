/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_heart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 21:23:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static float	heart_lobes(float x_scaled, float y_scaled, float max_radius)
{
	float lobe1_center = -0.5f;
	float lobe2_center = 0.5f;
	float lobe_y_center = 0.3f;
	float lobe_radius = 0.6f;
	float dist1 = sqrtf((x_scaled - lobe1_center) * (x_scaled - lobe1_center)
			+ (y_scaled - lobe_y_center) * (y_scaled - lobe_y_center));
	float dist2 = sqrtf((x_scaled - lobe2_center) * (x_scaled - lobe2_center)
			+ (y_scaled - lobe_y_center) * (y_scaled - lobe_y_center));
	float height1 = (dist1 < lobe_radius)
		? sqrtf(lobe_radius * lobe_radius - dist1 * dist1) : 0.0f;
	float height2 = (dist2 < lobe_radius)
		? sqrtf(lobe_radius * lobe_radius - dist2 * dist2) : 0.0f;
	if (dist1 < lobe_radius || dist2 < lobe_radius)
		return fmaxf(height1, height2) * max_radius * 0.3f;
	return 0.0f;
}

static float	heart_point(float x_scaled, float y_scaled, float max_radius)
{
	float point_factor = 1.0f + y_scaled;
	if (point_factor > 0.0f && fabsf(x_scaled) < point_factor * 0.8f)
	{
		float point_width = point_factor * 0.8f;
		float dist_from_center_line = fabsf(x_scaled);
		if (dist_from_center_line < point_width)
		{
			return max_radius * 0.2f * point_factor
				* (1.0f - dist_from_center_line / point_width);
		}
	}
	return 0.0f;
}

static float	heart_middle(float x_scaled, float max_radius)
{
	if (fabsf(x_scaled) < 0.8f)
		return max_radius * 0.15f * (0.8f - fabsf(x_scaled));
	return 0.0f;
}

static float	heart_volume(float u, float v, float max_radius)
{
	float overall_dist = sqrtf(u * u + v * v);
	if (overall_dist < 1.5f)
	{
		float volume_factor = 1.0f - overall_dist / 1.5f;
		return max_radius * 0.1f * volume_factor * volume_factor;
	}
	return 0.0f;
}

static float	heart_base(float z, float u, float v, float max_radius)
{
	float overall_dist = sqrtf(u * u + v * v);
	if (z > 0.0f && overall_dist > 1.2f && overall_dist < 1.5f)
	{
		float base_factor = (1.5f - overall_dist) / 0.3f;
		return max_radius * 0.05f * base_factor;
	}
	return z;
}

void	apply_heart_transformation(t_app *fdf)
{
	t_meta_shape	s;
	float			x_scaled;
	float			y_scaled;
	float			overall_dist;

	s.max_radius = fminf(fdf->width, fdf->height) / 4.0f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			s.s_vec.u = (2.0f * s.coord.x / (fdf->width - 1)) - 1.0f;
			s.s_vec.v = (2.0f * s.coord.y / (fdf->height - 1)) - 1.0f;
			s.s_vec.v = -s.s_vec.v;
			s.shape.x = s.s_vec.u * s.max_radius;
			s.shape.y = s.s_vec.v * s.max_radius;
			s.shape.z = 0.0f;
			x_scaled = s.s_vec.u * 2.0f;
			y_scaled = s.s_vec.v * 1.5f;
			if (y_scaled > 0.0f)
				s.shape.z = heart_lobes(x_scaled, y_scaled, s.max_radius);
			else if (y_scaled < 0.0f)
				s.shape.z = heart_point(x_scaled, y_scaled, s.max_radius);
			else
				s.shape.z = heart_middle(x_scaled, s.max_radius);
			s.shape.z += heart_volume(s.s_vec.u, s.s_vec.v, s.max_radius);
			overall_dist = sqrtf(s.s_vec.u * s.s_vec.u + s.s_vec.v * s.s_vec.v);
			s.shape.z = heart_base(s.shape.z, s.s_vec.u, s.s_vec.v, s.max_radius);
			s.shape.z += fdf->points[s.index] * 0.02f;
			s.sp[0] = s.shape.x;
			s.sp[1] = s.shape.y;
			s.sp[2] = s.shape.z;
			s.sp[3] = 1;
			s.dp = (float *)&fdf->transformed_points[s.index];
			matrix4_dot_product(fdf->transformation_stack.combined, s.sp, s.dp);
		}
	}
}
