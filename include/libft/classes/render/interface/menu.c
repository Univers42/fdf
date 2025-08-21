/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:06:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 13:06:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_menu(t_meta *meta)
{
	draw_controls(meta);
	draw_info(meta);
	draw_mapinfo(meta);
	draw_colorscheme(meta);
	if (meta->map.debug_mode)
	{
		print_str(meta, 10, 50, "== DEBUG MODE ==");
		print_str(meta, 10, 70, "Showing real Z values");
		print_str(meta, 10, 90, "Z-range:");
		print_nbr(meta, 80, 90, (int)meta->map.zmin);
		print_str(meta, 120, 90, "to");
		print_nbr(meta, 150, 90, (int)meta->map.limits.axis[Z]);
		print_str(meta, 10, 110, "Original Z-div:");
		print_nbr(meta, 130, 110, (int)meta->map.zdivisor);
		print_str(meta, 10, 130, "Points rendered:");
		print_nbr(meta, 140, 130, meta->map.len);
		print_str(meta, 10, 150, "Red=peaks Green=mid Blue=valleys");
	}
}
