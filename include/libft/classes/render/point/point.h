/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:46:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:51:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include "geometry.h"
# include "window.h"
# include "ft_math.h"

typedef enum e_terrain
{
	GROUND720 = 0xac7456,
	PURPLE1 = 0Xbfabcc,
	YELLOW_PALE = 0xdecd51,
	GREEN_TERRAIN = 0xaced99,
	PURPLE = 0Xac74f9,
	AQUA = 0x40cdbf,
	SHALLOW = 0X189995,
	DEEP = 0X555999,
	PURPLE2 = 0x60699b,
	PURPLE3 = 0x8879be,
	PURPLE4 = 0xac74f9,
	PINK = 0X997498,
	WHITE1 = 0xdeddcc,
	WHITE2 = 0xe9cab3,
	ORANGE = 0xc56930,
	ORANGE2 = 0Xc66a31,
	ORANGE3 = 0Xd77b34,
	YELLOW_TERRAIN = 0xe79b34,
	GREEN_PALE = 0xc5baa6,
	GREEN_PALE2 = 0xc2b8a5,
	BLUE_TERRAIN = 0X3babbf,
	BLUE2 = 0x3aaaaf,
	BLUE3 = 0X3ca9af,
	BLUE4 = 0x3a98ae
}			t_terrain;

typedef enum e_gamma
{
	gamma1 = 0xac74f9,
	gamma2 = 0x997498
}			t_gamma;

// Forward declaration for t_pixel (OOP-style point)
struct					s_pixel;
typedef struct s_pixel	t_pixel;

// Forward declaration for t_line to resolve circular dependency
struct					s_line;
typedef struct s_line	t_line;

// Use t_vec2, t_vec3, etc. from geometry.h
// (do not redefine them here)

// Vtable for OOP-style point
typedef struct s_point_vtable
{
	void	(*destroy)(t_pixel *self);
	void	(*get_coordinate)(t_pixel *self, t_vec2 *out);
	void	(*get_position)(t_pixel *self, t_position *out);
	void	(*get_color)(t_pixel *self, t_color *out);
	int		(*set_coordinate)(t_pixel *self, int x, int y);
	int		(*set_position)(t_pixel *self, double x, double y, double z);
	int		(*set_color)(t_pixel *self, uint32_t hex_color);
	int		(*set_z_value)(t_pixel *self, int z);
	int		(*translate)(t_pixel *self, int dx, int dy);
	int		(*scale)(t_pixel *self, double scale_x, double scale_y);
	t_pixel	*(*clone)(t_pixel *self);
}	t_point_vtable;

// OOP-style point struct
struct s_pixel
{
	t_vec2			coordinate;
	t_position		world_pos;
	t_color			color;
	t_point_vtable	*vtable;
	t_pos			pos;
	double			speed;
};

/* Constructor and destructor */
t_pixel		*point_new(int x, int y, int z);
t_pixel		*point_new_with_color(int x, int y, int z, uint32_t color);
void		point_destroy(t_pixel *point);

/* Static vtable functions */
void		point_get_coordinate(t_pixel *self, t_vec2 *out);
void		point_get_position(t_pixel *self, t_position *out);
void		point_get_color(t_pixel *self, t_color *out);
int			point_set_coordinate(t_pixel *self, int x, int y);
int			point_set_position(t_pixel *self, double x, double y, double z);
int			point_set_color(t_pixel *self, uint32_t hex_color);
int			point_set_z_value(t_pixel *self, int z);
int			point_translate(t_pixel *self, int dx, int dy);
int			point_scale(t_pixel *self, double scale_x, double scale_y);
t_pixel		*point_clone(t_pixel *self);
void		point_destroy_method(t_pixel *self);

/* Utility functions */
uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b);
void		hex_to_rgb(uint32_t hex, uint8_t *r, uint8_t *g, uint8_t *b);
double		euclidean_dist(t_pixel *p1, t_pixel *p2);
bool		point_equals(t_pixel *p1, t_pixel *p2);

#endif