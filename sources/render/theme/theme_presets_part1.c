/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme_presets_part1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:35:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 04:46:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	theme_preset_build_0(t_theme *t)
{
	t->name = "Planet/Ocean";
	t->background = create_color(0, 8, 20);
	t->rule_count = 4;
	t->rules[0] = rr(create_color(10, 25, 68), 0.00f, 0.30f);
	t->rules[1] = rr(create_color(18, 87, 122), 0.30f, 0.60f);
	t->rules[2] = rr(create_color(32, 155, 164), 0.60f, 0.85f);
	t->rules[3] = rr(create_color(180, 220, 230), 0.85f, 1.00f);
}

void	theme_preset_build_1(t_theme *t)
{
	t->name = "Default";
	t->background = create_color(0, 0, 0);
	t->rule_count = 4;
	t->rules[0] = rr(create_color(30, 30, 30), 0.00f, 0.25f);
	t->rules[1] = rr(create_color(80, 80, 80), 0.25f, 0.50f);
	t->rules[2] = rr(create_color(160, 160, 160), 0.50f, 0.75f);
	t->rules[3] = rr(create_color(220, 220, 220), 0.75f, 1.00f);
}

void	theme_preset_build_2(t_theme *t)
{
	t->name = "Gamma Random V2";
	t->background = create_color(5, 5, 16);
	t->rule_count = 4;
	t->rules[0] = rr(create_color(5, 5, 20), 0.00f, 0.25f);
	t->rules[1] = rr(create_color(90, 15, 120), 0.25f, 0.55f);
	t->rules[2] = rr(create_color(200, 40, 40), 0.55f, 0.80f);
	t->rules[3] = rr(create_color(250, 200, 60), 0.80f, 1.00f);
}

void	theme_preset_build_3(t_theme *t)
{
	t->name = "Vibrant/Rainbow";
	t->background = create_color(0, 0, 0);
	t->rule_count = 5;
	t->rules[0] = rr(create_color(255, 0, 64), 0.00f, 0.20f);
	t->rules[1] = rr(create_color(255, 128, 0), 0.20f, 0.45f);
	t->rules[2] = rr(create_color(64, 255, 0), 0.45f, 0.70f);
	t->rules[3] = rr(create_color(0, 200, 255), 0.70f, 0.85f);
	t->rules[4] = rr(create_color(160, 0, 255), 0.85f, 1.00f);
}
