/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include "libft/libft.h"

void	center_model(
	t_transformation_stack *t,
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
	transformation_stack_pan(t, 0,
		-result[1] * t->projection.box[1] / 2);
}
