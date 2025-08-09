/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme_presets_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:39:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 04:45:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_theme_rule	rr(uint32_t c, float a, float b)
{
	return ((t_theme_rule)
		{
			.color = c,
			.z_min = a,
			.z_max = b,
			.relative = true
		});
}

void	theme_preset_build_5(t_theme *t)
{
	t->name = "Sunset";
	t->background = create_color(20, 10, 40);
	t->rule_count = 4;
	t->rules[0] = rr(create_color(20, 10, 40), 0.00f, 0.30f);
	t->rules[1] = rr(create_color(120, 30, 90), 0.30f, 0.60f);
	t->rules[2] = rr(create_color(220, 80, 40), 0.60f, 0.85f);
	t->rules[3] = rr(create_color(255, 180, 60), 0.85f, 1.00f);
}

void	theme_preset_build_6(t_theme *t)
{
	t->name = "Matrix/Neon Green";
	t->background = create_color(0, 6, 0);
	t->rule_count = 4;
	t->rules[0] = rr(create_color(0, 8, 0), 0.00f, 0.25f);
	t->rules[1] = rr(create_color(0, 40, 0), 0.25f, 0.50f);
	t->rules[2] = rr(create_color(0, 120, 0), 0.50f, 0.75f);
	t->rules[3] = rr(create_color(40, 255, 90), 0.75f, 1.00f);
}

void	theme_preset_build_7(t_theme *t)
{
	t->name = "Fire/Lava";
	t->background = create_color(18, 0, 0);
	t->rule_count = 5;
	t->rules[0] = rr(create_color(20, 0, 0), 0.00f, 0.20f);
	t->rules[1] = rr(create_color(120, 10, 0), 0.20f, 0.45f);
	t->rules[2] = rr(create_color(200, 40, 0), 0.45f, 0.70f);
	t->rules[3] = rr(create_color(255, 160, 0), 0.70f, 0.90f);
	t->rules[4] = rr(create_color(255, 240, 180), 0.90f, 1.00f);
}

void	theme_preset_build_8(t_theme *t)
{
	t->name = "Ice/Arctic";
	t->background = create_color(0, 16, 32);
	t->rule_count = 4;
	t->rules[0] = rr(create_color(0, 10, 30), 0.00f, 0.25f);
	t->rules[1] = rr(create_color(0, 60, 120), 0.25f, 0.55f);
	t->rules[2] = rr(create_color(40, 140, 200), 0.55f, 0.80f);
	t->rules[3] = rr(create_color(160, 220, 255), 0.80f, 1.00f);
}
