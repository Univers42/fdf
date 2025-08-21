/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:10:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 00:41:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLORS_H
# define FT_COLORS_H

// Reset
# define RESET_TERM		"\033[0m"

// Regular colors
# define BLACK_TERM		"\033[0;30m"
# define RED_TERM		"\033[0;31m"
# define GREEN_TERM		"\033[0;32m"
# define YELLOW_TERM	"\033[0;33m"
# define BLUE_TERM		"\033[0;34m"
# define MAGENTA_TERM	"\033[0;35m"
# define CYAN_TERM		"\033[0;36m"
# define WHITE_TERM		"\033[0;37m"

// Bright colors
# define BRIGHT_BLACK_TERM	"\033[1;30m"
# define BRIGHT_RED_TERM	"\033[1;31m"
# define BRIGHT_GREEN_TERM	"\033[1;32m"
# define BRIGHT_YELLOW_TERM	"\033[1;33m"
# define BRIGHT_BLUE_TERM	"\033[1;34m"
# define BRIGHT_MAGENTA_TERM	"\033[1;35m"
# define BRIGHT_CYAN_TERM	"\033[1;36m"
# define BRIGHT_WHITE_TERM	"\033[1;37m"

// Dim and bold
# define DIM_TERM		"\033[2m"
# define BOLD_TERM      "\033[1m"

#endif