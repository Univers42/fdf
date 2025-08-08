/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_color.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:29:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 23:40:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWITCH_COLOR_H
# define SWITCH_COLOR_H
# include <stdint.h>
# include <stdbool.h>
# include "libft/math/geometry/draw/pixel.h"

/* Forward declaration */
typedef struct s_fdf t_app;

/* Palette function type */
typedef void (*palette_func_t)(int *arr, int pos, int z_value);

/* Singleton palette API */
int				palette_count(void);
int				palette_current(void);
void			palette_set(int idx, t_app *fdf);
palette_func_t	palette_get(int idx);

/* Backward compatibility */
palette_func_t	get_color_palette(int idx);
void			set_palette_index(int idx, t_app *fdf);
void			set_color_array(t_app *fdf);

/* Point providers using t_color structure */
const t_color	*planet_color_points(void);
int				planet_color_count(void);

const t_color	*gamma_random_v2_color_points(void);
int				gamma_random_v2_color_count(void);

const t_color	*vibrant_color_points(void);
int				vibrant_color_count(void);

const t_color	*grayscale_color_points(void);
int				grayscale_color_count(void);

const t_color	*matrix_color_points(void);
int				matrix_color_count(void);

/* Color interpolation */
uint32_t		lerp_color(uint32_t c1, uint32_t c2, float t);

#endif
