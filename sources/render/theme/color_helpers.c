/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:17:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 04:41:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b)
{
	return (((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b);
}

uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | (uint32_t)a);
}

static uint32_t	interpolate_theme_color(const t_theme *theme, float norm)
{
	float	segment_size;
	int		segment;
	float	local_t;

	segment_size = 1.0f / (theme->rule_count - 1);
	segment = (int)(norm / segment_size);
	if (segment >= theme->rule_count - 1)
		segment = theme->rule_count - 2;
	local_t = (norm - segment * segment_size) / segment_size;
	return (lerp_color(theme->rules[segment].color,
			theme->rules[segment + 1].color, local_t));
}

uint32_t	get_color_for_height(t_app *fdf, float norm)
{
	t_theme	theme;

	if (norm < 0)
		norm = 0;
	if (norm > 1)
		norm = 1;
	if (!fdf || fdf->palette_state.count == 0)
		return (create_color(128, 128, 128));
	if (fdf->palette_state.current < 0
		|| fdf->palette_state.current >= fdf->palette_state.count)
		fdf->palette_state.current = 0;
	theme_make_preset(fdf->palette_state.current, &theme);
	if (theme.rule_count <= 0 || theme.rule_count > 9)
		return (create_color(128, 128, 128));
	if (theme.rule_count == 1)
		return (theme.rules[0].color);
	return (interpolate_theme_color(&theme, norm));
}

void	theme_preset_build_4(t_theme *t)
{
	t->name = "Grayscale";
	t->background = create_color(0, 0, 0);
	t->rule_count = 5;
	t->rules[0] = rr(create_color(0, 0, 0), 0.00f, 0.20f);
	t->rules[1] = rr(create_color(64, 64, 64), 0.20f, 0.40f);
	t->rules[2] = rr(create_color(128, 128, 128), 0.40f, 0.60f);
	t->rules[3] = rr(create_color(192, 192, 192), 0.60f, 0.80f);
	t->rules[4] = rr(create_color(255, 255, 255), 0.80f, 1.00f);
}
