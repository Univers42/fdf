/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:53:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/26 13:36:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DS_H
# define DS_H

# include "config.h"
# include "ft_math.h"

/* Forward declaration for palette function type */
typedef void			(*t_palette_func)(int *, int, int);
typedef struct s_app	t_app;
// Handler type for composite key events with keycode context
typedef void			(*t_event_fn)(t_app*, int keycode, void*);

enum
{
	RNG_LCG = 0,
	RNG_XORSHIFT = 1,
	RNG_MIDDLE_SQUARE = 2
};

typedef struct s_palette_state
{
	t_palette_func	*funcs;
	int				count;
	int				current;
}					t_palette_state;

typedef struct s_transition_state
{
	int				frame;
	int				max_frames;
	bool			active;
	t_shape_type	current_shape;
	t_shape_type	target_shape;
	float			*original_positions;
	bool			initialized;
}					t_transition_state;

typedef struct s_bound
{
	int	x;
	int	y;
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
	t_texture_type	current_texture;
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
	t_dance_move		current_move;
	t_dance_move		next_move;
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
	t_object_effect_type	current_effect;
	bool					active;
	float					time_accumulator;
	float					intensity;
	bool					initialized;
	float					*original_points;
	int						total_points;
}							t_object_effects_system;

typedef struct s_dynamic_bg_system
{
	t_dynamic_bg_type	current_bg;
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

//could be replace by the point struct to modularize more
typedef struct s_trans_stack
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
}						t_trans_stack;

/**
 * 
 */
typedef struct s_bresenham_state
{
	int				delta[3];
	int				step[3];
	int				p1[3];
	int				p2[3];
	int				error_count;
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

typedef struct s_pivot
{
	void	*low;
	void	*mid;
	void	*high;
}			t_pivot;

typedef struct s_app
{
	void					*mlx;
	void					*window;
	void					*image;
	uint32_t				*color;
	float					*points;
	t_fpoint4				*transformed_points;
	int						(*edges)[2];
	int						width;
	int						height;
	int						min_z;
	int						max_z;
	size_t					n_edges;
	t_renderer				renderer;
	t_bresenham_state		bresenham_state;
	t_trans_stack			trans_stack;
	t_input_state			input_state;
	int						drag_start[2];
	bool					has_color;
	bool					auto_rotate;
	t_palette_state			palette_state;
	t_transition_state		transition_state;
	int						shadow_mode;
	int						current_bg_theme;
	int						stars_enabled;
	float					*noise_offsets; // was: float noise_offsets
	int						noise_size;
	uint32_t				*snapshot;
	int						color_count;
}							t_app;

struct s_pdraw
{
	int			px;
	int			py;
	int			size;
	uint32_t	color;
};

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

typedef struct s_generic_struct
{
	void	*a;
	void	*b;
	void	*c;
	void	*d;
}			t_generic_struct;

typedef struct s_pos_check
{
	int		x;
	int		index;
}			t_pos_check;

typedef struct s_pack_color
{
	uint32_t	color;
	uint32_t	bg_color;
}				t_pack_color;

typedef struct s_meta_shape
{
	float		max_radius;
	float		height_limit;
	struct
	{
		float	x;
		float	y;
		float	z;
	}			s_shape;
	struct
	{
		int		x;
		int		y;
	}			s_coord;
	struct
	{
		float	u;
		float	v;
	}			s_vec;
	struct
	{
		int	width;
		int	height;
		int	face;
		int	tot_point;
	}		s_face;
	struct
	{
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
	float		x;
	float		y;
	float		z;
	float		vx;
	float		vy;
	float		vz;
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

// Unified event binding (for both plain and combo events)
typedef struct s_event_binding
{
	t_event_key	key;
	t_event_fn	handler;
}				t_event_binding;

typedef struct s_particle_transition
{
	int				frame;
	int				max_frames;
	bool			active;
	t_particle_type	current_type;
	t_particle_type	target_type;
	t_particle		particles[MAX_PARTICLES];
	bool			initialized;
	float			time_accumulator;
}					t_particle_transition;

typedef struct s_z_perspective
{
	float	scale_factor;
	float	original_max_z;
	float	original_min_z;
	bool	initialized;
	float	*original_z_values;
	int		total_points;
}			t_z_perspective;

typedef struct s_wobble_point_params
{
	int		index;
	float	norm_x;
	float	norm_y;
	float	freq;
	float	intensity;
}			t_wobble_point_params;

// --- Add these lines for global trackball state access ---
typedef struct s_trackball_shape_state
{
	float	current_rotation[4];
	float	rotation_matrix[16];
	bool	is_active;
}	t_trackball_shape_state;

// Core handlers state singleton
typedef struct s_core_handlers_state
{
	bool	auto_rotate;
	int		mouse_x;
	int		mouse_y;
	float	camera_speed;
	bool	free_roam_mode;
	bool	initialized;
}	t_core_handlers_state;

// Global modifier state tracking
typedef struct s_modifier_state
{
	bool	ctrl_pressed;
	bool	shift_pressed;
	bool	alt_pressed;
}	t_modifier_state;

// Special keycode mapping for common X11 keys that are out of normal range
typedef struct s_keycode_map
{
	int	x11_keycode;
	int	mapped_keycode;
}	t_keycode_map;

// Event handler table singleton
typedef struct s_event_handler_table
{
	t_event_fn	handler_table[MAX_KEYCODE][MODIFIER_COMBO_COUNT];
	bool		initialized;
}				t_event_handler_table;

typedef struct s_trackball_state
{
	float	current_quat[4];
	float	last_quat[4];
	int		last_mouse_x;
	int		last_mouse_y;
	bool	active;
	bool	initialized;
}			t_trackball_state;

typedef struct s_retouch
{
	float	highlight;
	float	intensity;
	float	lines;
}			t_retouch;

typedef struct s_plasma_vars
{
	float	nx;
	float	ny;
	float	p1;
	float	p2;
	float	p3;
	float	p4;
	float	intensity;
}			t_plasma_vars;

typedef struct s_tube_vars
{
	float		br;
	float		hl;
	float		ang;
	float		r;
	float		h;
	t_fpoint2	c;
	t_fpoint2	d;
	float		gr;
	float		mr;
	float		cr;
}			t_tube_vars;

#endif