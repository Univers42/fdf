/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:51:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 22:57:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
#define CONFIG_H
# define DEFAULT_COLOR 0xFFFFFF
# define BUFF_SIZE 1024

# ifndef WIDTH_WIN
#  define WIDTH_WIN 1200
# endif

# ifndef HEIGHT_WIN
#  define HEIGHT_WIN 800
#endif

# define TITLE_WIN "thread of steel"

# define DEFAULT_SCALE 30
# define SCALE_INCREMENT 2
# define ROTATE_INCREMENT 30
# define SCALE_INCREMENT 0.1
# define TRANSLATION_INCREMENT 10
# define WATER_LEVEL 0
# define DESTROY_NOTIFY 17

#ifndef TRIM_RADIX
# define TRIM_RADIX (1 << 0)
#endif

#ifndef TRIM_SPACES
# define TRIM_SPACES (1 << 1)
#endif

#ifndef TRIM_NUMS
# define TRIM_NUMS (1 << 2)
#endif

# ifdef __linux__
#  define KEY_F1      65470
#  define KEY_F2      65471
#  define KEY_F3      65472
#  define KEY_F4      65473
#  define KEY_F5      65474
#  define KEY_F6      65475
#  define KEY_ALT_1   65281  // Alt+1
#  define KEY_ALT_2   65282  // Alt+2
#  define KEY_ALT_3   65283  // Alt+3
#  define KEY_ALT_4   65284  // Alt+4
#  define KEY_ALT_5   65285  // Alt+5
#  define KEY_ALT_6   65286  // Alt+6
# else
#  define KEY_F1      122
#  define KEY_F2      120
#  define KEY_F3      99
#  define KEY_F4      118
#  define KEY_F5      96
#  define KEY_F6      97
#  define KEY_ALT_1   18   // Alt+1 on Mac
#  define KEY_ALT_2   19   // Alt+2 on Mac
#  define KEY_ALT_3   20   // Alt+3 on Mac
#  define KEY_ALT_4   21   // Alt+4 on Mac
#  define KEY_ALT_5   23   // Alt+5 on Mac
#  define KEY_ALT_6   22   // Alt+6 on Mac
# endif

# ifdef __linux__
#  define KEY_ESC     65307
# else
#  define KEY_ESC     53
# endif

enum e_theme_idx
{
	THEME_DEFAULT = 0, // KEY_0 = 29
	THEME_DARK = 1,	   // KEY_1 = 18
	THEME_PUNK = 2,	   // KEY_2 = 19
	THEME_RETRO = 3,   // KEY_3 = 20
	THEME_EARTH = 4,   // KEY_4 = 21
	THEME_SPACE = 5,   // KEY_5 = 23
	THEME_COUNT
};


#endif