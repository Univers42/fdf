/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:03:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:23:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_mapinfo(t_meta *meta)
{
	int		line;

	line = MAPINFO_BOX;
	print_str(meta, MENU_TAB, line, "//// MAP INFO ////");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Size:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.len);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Xmax:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.limits.axis[X]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Ymax:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.limits.axis[Y]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Zmax:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.limits.axis[Z]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Zmin:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.zmin);
	line += LINE_SIZE;
}
