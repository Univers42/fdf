/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/03 01:27:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* Feature test macros - define before any system includes */
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# ifndef _BSD_SOURCE
#  define _BSD_SOURCE
# endif

# include "ft_string.h"
# include "ft_memory.h"
# include "ft_ctype.h"
# include "data_structures.h"
# include "ft_math.h"
# include "ft_stdlib.h"
# include "ft_stdio.h"
# include "ft_render.h"
# include "ft_debug.h"
# include "ft_colors.h"
# include "ft_stddef.h"
# include "ft_sort.h"

# include <unistd.h>
# include <signal.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>


#endif