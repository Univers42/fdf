/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheme_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:06:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:23:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	draw_colorscheme(t_meta *meta)
{
	int		line;

	line = COLORSCHEME_BOX;
	print_str(meta, MENU_TAB, line, "//// COLORSCHEME ////");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "0: DEFAULT");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "1: TERRAIN");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "2: BLACK & WHITE");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "3: WHITE & BLACK");
	line += LINE_SIZE;
}

static void	draw_controls(t_meta *meta)
{
	int		line;

	line = CONTROL_BOX;
	print_str(meta, MENU_TAB, line, "//// CONTROLS ////");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Scroll: Zom In/Out");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Left Click: Rotate X/Y axis");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Right Click: Move");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Arrows: Rotate X/Y axis");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Q/W: Rotate Z axis");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "+/-: Z Divisor");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "B/Ctr + B: Blending");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "P/I Parralell/Isometric Views");
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "F/C Fit/Center");
	line += LINE_SIZE;
}
