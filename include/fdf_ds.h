/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:53:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/26 15:57:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DS_H
# define FDF_DS_H

# include "config.h"
# include "ft_math.h"
# include "pixel.h"

/* Forward declaration for palette function type */
typedef void						(*t_palette_func)(int *, int, int);
typedef struct s_app				t_app;
typedef struct s_bresenham_state	t_bresenham_state;
typedef struct s_renderer			t_renderer;
// Handler type for composite key events with keycode context
typedef void						(*t_event_fn)(t_app*, int keycode, void*);

/**
 * small generic container to hold three related pointers (low, mid, high)
 * commonly used for median-of-three pivot selecction, quick swaps, or any
 * small 3-element grouping where element type varies.
 * NOTES:
 * - members are void*;; the struct does not own or manage the pointer memory
 * - Cast pointer to the appropritate type before dereferencing
 * - Keep usage local / stack allocate when possible; trivial
 */
typedef struct s_pivot
{
	void	*low;
	void	*mid;
	void	*high;
}	t_pivot;

struct s_pdraw
{
	int			px;
	int			py;
	int			size;
	uint32_t	color;
	float		alpha;
	int			add;
};

/**
 * legacy code
 */
typedef struct s_generic_struct
{
	void	*a;
	void	*b;
	void	*c;
	void	*d;
}	t_generic_struct;

//================== EVENT STRUCT =========================
/**
 * 
 */
//=========================================================
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
}	t_event_handler_table;

typedef struct s_event_key
{
	int				keycode;
	unsigned int	modifiers;
}	t_event_key;

// Unified event binding (for both plain and combo events)
typedef struct s_event_binding
{
	t_event_key	key;
	t_event_fn	handler;
}	t_event_binding;

//================== RENDER STRUCT =========================
/**
 * 
 */
//=========================================================

typedef struct s_pack_color
{
	uint32_t	color;
	uint32_t	bg_color;
}	t_pack_color;

typedef struct s_particle
{
	float		x;
	float		y;
	float		z;
	float		vx;
	float		vy;
	float		vz;
	float		size;
	float		phase;
	uint32_t	color;
	float		lifetime;
	float		life0;
	bool		active;
}	t_particle;

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
}	t_particle_transition;

/**
 * Hold all state needed to drive a Bresenham line rasterization
 * loop. This struct is intended to be filled once per-line
 * and then read by the inner drawing loop (and helper functions)
 * so that the per-pixel logic receives all needed data through
 * a single pointer
 */
typedef struct s_bresenham_state
{
	int			delta[3];		// absolute diff along each axis
	int			step[3];		// step direction (-1, 0, +1) for each axis
	int			p1[3];			// start point corrdinates (x,y,z)
	int			p2[3];			// end point coordinates (x,y,z)
	int			error_count;	// primary Bresenham error accumulator
	uint32_t	color1;			// packed start color
	uint32_t	color2;			// packed end color
	int32_t		cfx[3];			// 12.20 fixed-point r,g,b accumulators
	int32_t		cfx_d[3];		// 12.20 fixed-point per-step increments
}	t_bresenham_state;

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

/**
 * s_renderer
 * 
 * PURPOSE:
 * 	small container for image/framebuffer metadata used by draw back
 * NOTES:
 * 	keep bpp/size_line/is_big_endian consistent with the window API
 */
typedef struct s_renderer
{
	char			fps_string[10];	//human readable fps text buffer
	int				fps;			//last measured frames-per-second int
	char			*data;			//pointer to pxl buffer provided b the win
	int				bpp;			//bits per pixel
	int				size_line;		//nbr bytes per row (stride)
	int				is_big_endian;	//non-zero if the backend expects big-endian
}	t_renderer;

typedef struct s_palette_state
{
	t_palette_func	*funcs;
	int				count;
	int				current;
}	t_palette_state;

typedef struct s_transition_state
{
	int				frame;
	int				max_frames;
	bool			active;
	t_shape_type	current_shape;
	t_shape_type	target_shape;
	float			*cloud_src;
	float			*cloud_dst;
}	t_transition_state;

typedef struct s_bound
{
	int	x;
	int	y;
}	t_bound;

/**
 * ?radial distance from the origin (>=0).
 * Represents how far the point is from the center.
 * ?Radius_base--baseline/rest radius.
 * EXAMPLE:
 * radius = radius_base + woblle
 * doing this we keep the refereence value separate from
 * a time-varying radius.
 * ?THETA
 * EXAMPLE:
 * ?PHI--the other spherical angle.
 * In math convention `phi=azimuth in XY plane(0..PI_2).
 * In graphic convention `phi=elevation(-PI/2...PI/2).
 * EXAMPLE:
 * ?ANGLE--generic  rotation/phase angle (usually in radians).
 * Often used as an animation phase (increment each frame) or
 * a single-place rotation around an axis.
 * !IMPORTANT NOTE: two common mmapping to Cartesian Coordinates
 * *Math (physics / mathematics) convention
 * - theta = inclination from + Z,, phi = azimuth in XY
 * plane x = r * sin(theta) * cos(phi) y = r*sin(theta)*
 * sin(phi) z = r * cos(theta)
 * *Graphics / engineering convention (theta = azimmuth, phi=elevation)
 * - theta =  azimuth (angle in XY), phi = elevation(angle above XY)x
 * = r * cos(phi) * cos(theta)y = r * cos(phi);
 * EXAMPLE:
 * * float r = trigo->radius_base + 0.5f * sinf(trigo->angle); // animated radius
 * * float theta = trigo->theta; // azimuth
 * * float phi   = trigo->phi;   // elevation
 * * float cx = r * cosf(phi) * cosf(theta);
 * * float cy = r * cosf(phi) * sinf(theta);
 * * float cz = r * sinf(phi);
 */
typedef struct s_trigo
{
	float	radius;	//Represent how far the point is from the center
	float	theta;	//
	float	phi;	//polar/inclination measured
	float	angle;	
	float	radius_base;
}	t_trigo;

/**
 * simple boundary structure to verify collisions
 * For future project !
 */
typedef struct s_fbound
{
	float	min;
	float	max;
}	t_fbound;

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
	uint32_t		*fade_from;
	int				fade_left;
	bool			fade_pending;
	int				frame;
}	t_texture_system;

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
}	t_dance_system;

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
}	t_dynamic_bg_system;

typedef struct s_draw_char_params
{
	uint32_t	*buf;
	uint32_t	color;
	int			x;
	int			y;
}	t_draw_char_params;

//================== PARSER STRUCT =========================
/**
 * 
 */
//=========================================================

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
}	t_parser;

/**
 * 
 */
typedef struct s_pos_check
{
	int		x;
	int		index;
}	t_pos_check;

//================== TRANSFORM STRUCT =========================
/**
 * 
 */
//=========================================================

typedef struct s_z_perspective
{
	float	scale_factor;
	float	original_max_z;
	float	original_min_z;
	bool	initialized;
	float	*original_z_values;
	int		total_points;
}	t_z_perspective;

typedef struct s_wobble_point_params
{
	int		index;
	float	norm_x;
	float	norm_y;
	float	freq;
	float	intensity;
}	t_wobble_point_params;

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

typedef struct s_trackball_state
{
	float	current_quat[4];
	float	last_quat[4];
	int		last_mouse_x;
	int		last_mouse_y;
	bool	active;
	bool	initialized;
}	t_trackball_state;

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
}	t_tube_vars;

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

typedef struct s_object_effects_system
{
	t_object_effect_type	current_effect;
	bool					active;
	float					time_accumulator;
	float					intensity;
	bool					initialized;
	float					*original_points;
	int						total_points;
}	t_object_effects_system;

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
}	t_projection_ctl;

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
}	t_trans_stack;

//================== FILTER STRUCT =========================
/**
 * PURPOSE:
 * hold small, POD types used bby image / post-process filter
 * This selection declares light-weight descripoors (state,
 * kerners, LUTs, chains) used by filter code; actual large
 * buffers should be allocated/owned by the implementation
 * NOTE:
 * - keep structs plain-old-data (no hidden ownership)
 * for pointer members: "owned by caller" or "owned by this
 * subsystem"
 * - Provide fixed-size storage for small kernels (3x3, 5x5)
 * - use floats for weights / intensities and ints for discrete sizes
 * !Filter are not thread safe
 * 
 * EXAMPLE:
 * create init a t_filter_state or t_filter_chai via init_fn
 * build_kernel/LUTs (owned by caller or via init helper)
 * call filter_apply(renderer->data, width, height, &chain)
 * free owned resources with provided free helpers
 */
//=========================================================

typedef struct s_retouch
{
	float	highlight;
	float	intensity;
	float	lines;
}	t_retouch;

typedef struct s_plasma_vars
{
	float	nx;
	float	ny;
	float	p1;
	float	p2;
	float	p3;
	float	p4;
	float	intensity;
}	t_plasma_vars;

/**
 * s_app
 * 
 * PURPOSE:
 * 	Central application state. Aggregates windowing handled, buffers,
 * scenve geometry, subsystem states and runtime flags used accross the
 * programm.
 * 
 * Quick overview:
 *	- backend handles: mlx, window, image
 *  - buffers / geometry: colors, points, tranformed_points, edges, 
 snapshots
 * 	- map metadata: width, height, min_z, max_z, n_edges
 *	- subsystem: renderer, bre
 * NOTES:
 * - MOST pointer members are owned by the application and should be
 * freed on shutdown unless documented otherwise
 * - This struct is not thread-safe; access must be syncrhonized
 * if used concurrently
 */
typedef struct s_app
{
	void				*mlx;				//	ctx_backend (mlx_pointer)
	void				*window;			//	window handle
	void				*image;				//	mlx_image
	uint32_t			*color;				//	pixel / color buffer
	float				*points;			//	map vertex positions(x,y,z,...)
	t_fpoint4			*transformed_points; // transformed vertices
	int					width;				// map width (points per row)
	int					height;				// map height (number of rows)
	int					min_z;				// min z value in map
	int					max_z;				// max z value in map
	size_t				n_edges;			// number of edges in `edges`
	t_renderer			renderer;			// framebuffer  / renderer metadata
	t_bresenham_state	bresenham_state;	// Bresenham rasterization state
	t_trans_stack		trans_stack;		// transformation / projection
	t_input_state		input_state;		// current input state
	int					drag_start[2];		// drag start coords [x,y] mouse
	bool				has_color;			// contains vertex.has(colors)
	bool				auto_rotate;		// auto-rotate scene flag
	t_palette_state		palette_state;		// palette subsystem state
	t_transition_state	transition_state;	// shape/scene transition state
	int					shadow_mode;		// current shadow mode selector
	int					current_bg_theme;	// current background/theme index
	int					stars_enabled;		// starts effeect enabled
	float				*noise_offsets;		// optional per-point noise effects
	int					noise_size;			// length of noise_offsets array
	uint32_t			*snapshot;		// optional snapshot buffer
	int					color_count;	// number of colors / palette entries
	bool				needs_redraw;	// dirty flag, skip render if clean
}						t_app;

/**
 * Black-hole background state (see black_hole_init.c for the LUT build).
 * lut: per screen pixel, packed source coord (sx | sy<<16) into the star
 * texture; sy == 0xFFFF is a sentinel: sx indexes palette[] instead
 * (0 = event horizon black, 1..255 = photon-ring gradient).
 */
typedef struct s_black_hole
{
	uint32_t	*lut;
	uint32_t	*stars;
	uint32_t	palette[256];
	float		photon_r;
	float		einstein_r;
	bool		init;
	bool		failed;
}	t_black_hole;

/**
 * One triangle ready for rasterization: screen coords, NDC depth per
 * vertex, one flat color (grid cells are tiny, flat == Gouraud here).
 */
typedef struct s_tri
{
	int			x[3];
	int			y[3];
	float		z[3];
	uint32_t	color;
}	t_tri;

/* Incremental edge-function state for one triangle fill. */
typedef struct s_tri_ctx
{
	int			bb[4];
	int			a[3];
	int			b[3];
	int			w[3];
	float		z;
	float		dzdx;
	float		dzdy;
}	t_tri_ctx;

/* Camera basis vectors + projection scales, passed to camera_rows. */
typedef struct s_cam_basis
{
	float	r[3];
	float	u[3];
	float	f[3];
	float	s[2];
}	t_cam_basis;

/* Free-fly first-person camera (world = grid units, z up). */
typedef struct s_camera
{
	float	pos[3];
	float	yaw;
	float	pitch;
	float	fov;
	bool	active;
}	t_camera;

/*
 * Runtime window size (viewport). The framebuffer stays at the
 * compile-time WIN_WIDTH x WIN_HEIGHT maximum (stride and clip bounds
 * unchanged); rendering targets the viewport and X clips the rest.
 */
typedef struct s_win_attr
{
	int	w;
	int	h;
}	t_win_attr;

typedef struct s_viewport
{
	int	w;
	int	h;
	int	settle;
	int	preset;
	int	tick;
}	t_viewport;

#endif
