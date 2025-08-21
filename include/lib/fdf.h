/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:47:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 14:00:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H
#include "libft/libft.h"
#include "libft/classes/render/camera/camera.h"
#include "libft/classes/render/map/map.h"
#include "libft/classes/trace/error/err_handler.h"

// Forward declaration for t_map if not included by map.h
#ifndef T_MAP_DEFINED
typedef struct s_map t_map;
#define T_MAP_DEFINED
#endif

typedef struct s_fdf
{
	t_handler err;      // Error handler integrated into the structure
	t_window *window;   // Main rendering window
	t_camera *view;     // Camera/view transformation
	t_line *line;       // Line rendering system
	t_map *map;         // Map/wireframe data
	t_arena *arena;
} t_app;

#endif