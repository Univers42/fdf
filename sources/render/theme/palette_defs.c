/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_defs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:21:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 04:26:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	theme_preset_count(void)
{
	return (9);
}

static t_theme	init_theme(void)
{
	return ((t_theme){
		.name = "Unknown",
		.background = create_color(0, 0, 0),
		.rule_count = 0
	});
}

void	theme_make_preset(int idx, t_theme *out)
{
	if (!out)
		return ;
	if (idx < 0 || idx >= theme_preset_count())
		idx = 0;
	*out = init_theme();
	if (idx == 0)
		return (theme_preset_build_0(out));
	if (idx == 1)
		return (theme_preset_build_1(out));
	if (idx == 2)
		return (theme_preset_build_2(out));
	if (idx == 3)
		return (theme_preset_build_3(out));
	if (idx == 4)
		return (theme_preset_build_4(out));
	if (idx == 5)
		return (theme_preset_build_5(out));
	if (idx == 6)
		return (theme_preset_build_6(out));
	if (idx == 7)
		return (theme_preset_build_7(out));
	if (idx == 8)
		return (theme_preset_build_8(out));
}
