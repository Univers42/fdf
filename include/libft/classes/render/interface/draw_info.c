/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:05:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:23:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_info(t_meta *meta)
{
	int		line;

	line = DRAWINFO_BOX;
	print_str(meta, MENU_TAB, line, "//// DRAW INFO ////");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Reenders:");
	print_nbr(meta, MENU_TAB + 100, line, meta->map.renders);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Performance(ms):");
	print_nbr(meta, MENU_TAB + 170, line, meta->map.performance * 1000);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "X, Y, Z: [   ] [   ] [   ]");
	print_nbr(meta, MENU_TAB + 100, line, meta->map.ang[X]);
	print_nbr(meta, MENU_TAB + 160, line, meta->map.ang[Y]);
	print_nbr(meta, MENU_TAB + 220, line, meta->map.ang[Z]);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Zoom:");
	print_nbr(meta, MENU_TAB + 80, line, meta->map.scale);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Z Divisor:");
	print_nbr(meta, MENU_TAB + 110, line, meta->map.zdivisor);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Blending:");
	print_nbr(meta, MENU_TAB + 100, line, meta->map.brange * 10000);
}
