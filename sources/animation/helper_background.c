/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bakcground.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:14:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:15:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	dynamic_background_is_active(void)
{
	return (gdynbg(NULL)->current_bg != DYNAMIC_BG_STATIC);
}

void	dynamic_background_set_speed(float speed)
{
	t_dynamic_bg_system	*db;

	db = gdynbg(NULL);
	if (speed < 0.1f)
		speed = 0.1f;
	if (speed > 5.0f)
		speed = 5.0f;
	db->animation_speed = speed;
	ft_printf("Dynamic BG speed: %.1fx\n", db->animation_speed);
}
