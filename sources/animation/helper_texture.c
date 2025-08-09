/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:19:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:20:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	texture_system_toggle(void)
{
	t_texture_system	*t;
	t_texture_type		next;
	const char			**names;

	t = gtexture(NULL);
	next = (t->current_texture + 1) % TEXTURE_COUNT;
	t->current_texture = next;
	t->time_accumulator = 0.0f;
	names = tex_name_tbl();
	ft_printf("Texture -> %s\n", names[next]);
}

bool	texture_system_is_active(void)
{
	return (gtexture(NULL)->current_texture != TEXTURE_NONE);
}

void	texture_system_set_scale(float scale)
{
	t_texture_system	*t;

	t = gtexture(NULL);
	if (scale < 0.1f)
		scale = 0.1f;
	if (scale > 5.0f)
		scale = 5.0f;
	t->scale_factor = scale;
}

void	texture_system_set_speed(float speed)
{
	t_texture_system	*t;

	t = gtexture(NULL);
	if (speed < 0.0f)
		speed = 0.0f;
	if (speed > 3.0f)
		speed = 3.0f;
	t->animation_speed = speed;
}
