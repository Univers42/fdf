/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:53:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 17:39:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DS_H
#define DS_H

#include "config.h"

typedef struct s_bound
{
	int	min;
	int	max;
}		t_bound;

typedef struct s_trigo
{
	float	radius;
	float	theta;
	float	phi;
	float	angle;
	float	radius_base;
}			t_trigo;

typedef struct s_fbound
{
	float	min;
	float	max;
}			t_fbound;

// no member structure
typedef struct s_texture_system
{
	t_texture_type	current_texture;		//enum
	bool			active;
	float			time_accumulator;
	float			scale_factor;
	bool			initialized;
	uint32_t		*original_colors;
	int				total_points;
	float			animation_speed;
}					t_texture_system;


typedef struct s_dance_system
{
	bool				active;
	t_dance_move		current_move;		//enum
	t_dance_move		next_move;			//enum
	float				time_accumulator;
	float				move_intensity;
	int					move_frame;
	int					hold_frame;
	bool				transitioning;
	bool				auto_sequence;
	float				*original_points;
	bool				initialized;
	int					total_points;
	float				rhythm_multiplier;
}						t_dance_system;



typedef struct s_object_effects_system
{
	t_object_effect_type	current_effect;		//enum
	bool					active;
	float					time_accumulator;
	float					intensity;
	bool					initialized;
	float					*original_points;
	int						total_points;
}							t_object_effects_system;



typedef struct s_dynamic_bg_system
{
	t_dynamic_bg_type	current_bg;	//enum
	bool				active;
	float				time_accumulator;
	float				intensity;
	bool				initialized;
	uint32_t			*bg_buffer;
	float				animation_speed;
	int					frame_counter;
}						t_dynamic_bg_system;

typedef struct s_draw_char_params
{
	uint32_t	*buf;
	uint32_t	color;
	int			x;
	int			y;
}				t_draw_char_params;

typedef struct s_parser
{
	char			*buf;
	ssize_t			bytes_read;
	size_t			values_read;
	size_t			arr_capacity;
	uint32_t		color;
	int				x;
	int				y;
	int				z;
	int				min_z;
	int				max_z;
	bool			z_set;
	bool			width_set;
}					t_parser;

typedef struct s_point4
{
	float	x;
	float	y;
	float	z;
	float	w;
}			t_point4;



typedef struct s_projection_ctl
{
	float			box[3];
	float			zoom_factor;
	float			pan_x;
	float			pan_y;
	float			l;
	float			r;
	float			t;
	float			b;
	float			f;
	float			n;
}					t_projection_ctl;

//!to replace with the below structure but little by little
typedef struct s_transformation_stack
{
	float				matrices[M_COUNT][16];
	float				temp[16];
	float				combined[16];
	bool				dirty[M_COUNT];
	t_projection_ctl	projection;
	float				px;
	float				pz;
	float				px2;
	float				rx;
	float				ry;
	float				rz;
	float				tx;
	float				ty;
	float				tz;
	float				ox;
	float				oy;
	float				oz;
}						t_transformation_stack;

//typedef struct	s_transformation_stack
//{
//	float	matrices[M_COUNT][16];
//	float	temp[16];
//	float	combined[16];
//	bool	dirty[M_COUNT];
//	t_projection_ctl	projection;
//	t_point3		r;
//	t_point3		t;
//	t_point3		p;
//	t_point3		o;
//}t_transormation_stack;

typedef struct s_bresenham_state
{
	int				delta[3];
	int				step[3];
	int				p1[3];
	int				p2[3];
	int				error_count;
	//t_color			color1;
	//t_color			color2;
	uint32_t		color1;
	uint32_t		color2;
	float			color_r_delta;
	float			color_g_delta;
	float			color_b_delta;
}					t_bresenham_state;

typedef struct s_renderer
{
	char			fps_string[10];
	int				fps;
	char			*data;
	int				bpp;
	int				size_line;
	int				is_big_endian;
}					t_renderer;



typedef struct s_fdf
{
	void					*mlx;
	void					*window;
	void					*image;
	uint32_t				*color;
	float					*points;
	t_point4				*transformed_points;
	int						(*edges)[2];
	int						width;
	int						height;
	int						min_z;
	int						max_z;
	//t_bound					z_range;
	//t_bound					dim_win;
	size_t					n_edges;
	t_renderer				renderer;
	t_bresenham_state		bresenham_state;
	t_transformation_stack	transformation_stack;
	t_input_state			input_state;
	int						drag_start[2];
	bool					has_color;
}							t_app;

/**
 * Struct holding the context for the Bresenham drawing loop.
 * Used to avoid more than 4 arguments per function (norminette).
 */
typedef struct s_bresenham_ctx
{
	t_bresenham_state	*bresenham;
	unsigned int		*screen;
	int					coord[2];
	int					limit;
	int					major_axis;
}						t_bresenham_ctx;

typedef struct s_meta_shape
{
	float		max_radius;
	float		height_limit;
	struct {
		float	x;
		float	y;
		float	z;
	}			shape;
	struct {
		int		x;
		int		y;
	}			coord;
	struct {
		float	u;
		float	v;
	}			s_vec;
	struct {
		int	width;
		int	height;
		int	face;
		int	tot_point;
	}		s_face;
	struct {
		int	idx;
		int	x;
		int	y;
	}		s_loc;
	struct 
	{
		float	x;
		float	y;
	}			s_scale;
	struct
	{
		float	one;
		float	two;
		float	three;
		float	z;		
	}			s_wave;
	int			index;
	float		phase;
	float		height;
	float		sp[4];
	float		*dp;
	t_trigo		trigo;
	int			total_points;
	float		dist_center;
}				t_meta_shape;


typedef struct s_particle
{
	float		x, y, z;
	float		vx, vy, vz;
	float		size;
	uint32_t	color;
	int			lifetime;
	bool		active;
}				t_particle;

typedef struct s_event_key
{
	int				keycode;
	unsigned int	modifiers;
}					t_event_key;

// Handler type for composite key events with keycode context
typedef void (*t_event_fn)(t_app*, int keycode, void*);

// Unified event binding (for both plain and combo events)
typedef struct s_event_binding
{
	t_event_key	key;
	t_event_fn	handler;
}				t_event_binding;

typedef struct s_particle_transition
{
	int					frame;
	int					max_frames;
	bool				active;
	t_particle_type		current_type;
	t_particle_type		target_type;
	t_particle			particles[MAX_PARTICLES];
	bool				initialized;
	float				time_accumulator;
}						t_particle_transition;

#endif