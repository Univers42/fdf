/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:26:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 04:34:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "memory.h"

// Helper: compute absolute z ranges for theme rules
static void	compute_absolute_rules(const t_theme *theme,
					t_app *fdf, t_abs_rule *ar)
{
	int					i;
	float				zrange;
	const t_theme_rule	*r;

	zrange = (float)(fdf->max_z - fdf->min_z);
	if (zrange == 0.0f)
		zrange = 1.0f;
	i = -1;
	while (++i < theme->rule_count)
	{
		r = &theme->rules[i];
		if (r->relative)
		{
			ar[i].min_z = (float)fdf->min_z + r->z_min * zrange;
			ar[i].max_z = (float)fdf->min_z + r->z_max * zrange;
		}
		else
		{
			ar[i].min_z = r->z_min;
			ar[i].max_z = r->z_max;
		}
		if (ar[i].min_z > ar[i].max_z)
			ft_swap(&ar[i].min_z, &ar[i].max_z, sizeof(float));
		ar[i].color = r->color;
	}
}

// Helper: find color for z value using theme rules
static int	find_theme_color_for_z(float z, t_abs_rule *ar, int rule_count)
{
	int	k;

	k = -1;
	while (++k < rule_count)
		if (z >= ar[k].min_z && z <= ar[k].max_z)
			return (k);
	return (-1);
}

// Helper: clamp color to nearest band if no match
static uint32_t	clamp_theme_color(float z, t_abs_rule *ar, int rule_count)
{
	if (z < ar[0].min_z)
		return (ar[0].color);
	else
		return (ar[rule_count - 1].color);
}

// Main: apply theme to map
void	apply_theme_to_map(t_app *fdf, const t_theme *theme)
{
	t_abs_rule	ar[9];
	int			i;
	int			k;
	int			rule_count;
	float		z;

	if (!fdf || !theme || !fdf->points || !fdf->color || theme->rule_count <= 0)
		return ;
	rule_count = theme->rule_count;
	compute_absolute_rules(theme, fdf, ar);
	i = -1;
	while (++i < fdf->width * fdf->height)
	{
		z = fdf->points[i];
		k = find_theme_color_for_z(z, ar, rule_count);
		if (k >= 0)
			fdf->color[i] = ar[k].color;
		else
			fdf->color[i] = clamp_theme_color(z, ar, rule_count);
	}
}
