/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:13:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_projection(t_projection_ctl *p)
{
	if (p->zoom_factor < 0.001f)
	{
		p->n = 0.00001f;
		p->f = p->box[2] * 10000.0f;
	}
	else if (p->zoom_factor < 0.1f)
	{
		p->n = 0.0001f;
		p->f = p->box[2] * 1000.0f;
	}
	else if (p->zoom_factor > 1000.0f)
	{
		p->n = 0.000001f;
		p->f = p->box[2] * 0.1f;
	}
	else if (p->zoom_factor > 10.0f)
	{
		p->n = 0.00001f;
		p->f = p->box[2] * 1.0f;
	}
	else
	{
		p->n = 0.01f;
		p->f = p->box[2] * 2.0f;
	}
}

void	center_model(
	t_trans_stack *t,
	float width,
	float height,
	float depth
) {
	float	vec[4];
	float	result[4];

	vec[0] = width / 2;
	vec[1] = height / 2;
	vec[2] = depth / 2;
	vec[3] = 1;
	matrix4_dot_product(t->combined, vec, result);
	trans_stack_pan(t, 0,
		-result[1] * t->projection.box[1] / 2);
}
