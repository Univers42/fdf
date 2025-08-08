/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 16:47:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include "ft_math.h"

float	calculate_wobble_axis(float freq, float *multipliers,
								float *scales)
{
	float	comp1;
	float	comp2;
	float	comp3;
	float	result;

	comp1 = calculate_wobble_component(freq, multipliers[0], scales[0]);
	comp2 = calculate_wobble_component(freq, multipliers[1], scales[1]);
	comp3 = calculate_wobble_component(freq, multipliers[2], scales[2]);
	result = (comp1 + comp2 + comp3) * scales[3];
	return (result);
}

static void	init_wobble_params(float x_params[2][4], float y_params[2][4])
{
	x_params[0][0] = 1.0f;
	x_params[0][1] = 2.7f;
	x_params[0][2] = 4.3f;
	x_params[1][0] = 1.0f;
	x_params[1][1] = 0.7f;
	x_params[1][2] = 0.4f;
	x_params[1][3] = 0.05f;
	y_params[0][0] = 1.9f;
	y_params[0][1] = 3.1f;
	y_params[0][2] = 5.7f;
	y_params[1][0] = 1.0f;
	y_params[1][1] = 0.6f;
	y_params[1][2] = 0.3f;
	y_params[1][3] = 0.04f;
}

static void	apply_rotation_wobble(t_app *fdf, float freq, float intensity)
{
	t_point3	wobble;
	float		params[2][4];

	init_wobble_params(params, params);
	wobble.x = calculate_wobble_axis(freq, params[0], params[1]);
	params[0][0] = 1.9f;
	params[0][1] = 3.1f;
	params[0][2] = 5.7f;
	params[1][0] = 1.0f;
	params[1][1] = 0.6f;
	params[1][2] = 0.3f;
	params[1][3] = 0.04f;
	wobble.y = calculate_wobble_axis(freq, params[0], params[1]);
	params[0][0] = 1.4f;
	params[0][1] = 3.8f;
	params[0][2] = 6.2f;
	params[1][0] = 1.0f;
	params[1][1] = 0.8f;
	params[1][2] = 0.2f;
	params[1][3] = 0.03f;
	wobble.z = calculate_wobble_axis(freq, params[0], params[1]);
	trans_stack_rotate_x(&fdf->trans_stack, wobble.x * intensity);
	trans_stack_rotate_y(&fdf->trans_stack, wobble.y * intensity);
	trans_stack_rotate_z(&fdf->trans_stack, wobble.z * intensity);
}

static void	apply_point_wobbles(t_wobble_point_params *params, t_app *fdf)
{
	float	w1;
	float	w2;
	float	w3;
	float	w4;
	float	total;

	w1 = sinf((params->norm_x + g_dance.time_accumulator * params->freq * 1.2f)
			* M_PI * 6.0f);
	w2 = cosf((params->norm_y + g_dance.time_accumulator * params->freq * 1.8f)
			* M_PI * 4.0f);
	w3 = sinf(((params->norm_x + params->norm_y) + g_dance.time_accumulator
				* params->freq * 2.3f) * M_PI * 5.0f);
	w4 = cosf((params->norm_x * params->norm_y + g_dance.time_accumulator
				* params->freq * 0.7f) * M_PI * 8.0f);
	total = (w1 + w2 + w3 + w4) * 15.0f * params->intensity;
	fdf->points[params->index] = g_dance.original_points[params->index] + total;
}

void	apply_dance_wobble(t_app *fdf)
{
	t_wobble_point_params	params;
	int						y;
	int						x;

	params.freq = 8.0f * g_dance.rhythm_multiplier;
	params.intensity = g_dance.move_intensity;
	apply_rotation_wobble(fdf, params.freq, params.intensity);
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			params.index = y * fdf->width + x;
			params.norm_x = (float)x / fdf->width;
			params.norm_y = (float)y / fdf->height;
			apply_point_wobbles(&params, fdf);
			x++;
		}
		y++;
	}
}
