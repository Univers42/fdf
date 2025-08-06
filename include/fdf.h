/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:51:48 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/06 04:28:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

# ifndef WIN_WIDTH
#  define WIN_WIDTH 2920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 2000
# endif

# if WIN_HEIGHT * WIN_WIDTH < 32
#  error "window height * window width must be greater than 32"
# endif

typedef struct s_draw_char_params
{
	uint32_t	*buf;
	uint32_t	color;
	int			x;
	int			y;
}	t_draw_char_params;

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

typedef struct s_point4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_point4;

typedef enum e_matrices
{
	M_PROJECTION,
	M_VIEW_ROTATE_X2,
	M_TB,
	M_ROTATION_Z,
	M_ROTATION_X,
	M_ROTATION_Y,
	M_VIEW_ROTATE_X,
	M_VIEW_ROTATE_Z,
	M_ORIGIN,
	M_COUNT,
}	t_matrices;

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

typedef struct s_transformation_stack
{
	float				matrices[M_COUNT][16];
	float				temp[16];
	float				combined[16];
	bool				dirty[M_COUNT];
	t_projection_ctl	projection;
	float				px;
	float				px2;
	float				pz;
	float				rx;
	float				ry;
	float				rz;
	float				tx;
	float				ty;
	float				tz;
	float				ox;
	float				oy;
	float				oz;
}	t_transformation_stack;

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
}	t_bresenham_state;

typedef struct s_renderer
{
	char			fps_string[10];
	int				fps;
	char			*data;
	int				bpp;
	int				size_line;
	int				is_big_endian;
}	t_renderer;

typedef enum e_input_state
{
	INPUT_STATE_IDLE,
	INPUT_STATE_DRAGGING,
	INPUT_STATE_ROTATING,
}	t_input_state;

typedef struct s_fdf
{
	uint32_t				*color;
	float					*points;
	t_point4				*transformed_points;
	int						(*edges)[2];
	int						width;
	int						height;
	int						min_z;
	int						max_z;
	size_t					n_edges;
	void					*mlx;
	void					*window;
	void					*image;
	t_renderer				renderer;
	t_bresenham_state		bresenham_state;
	t_transformation_stack	transformation_stack;
	t_input_state			input_state;
	int						drag_start[2];
	bool					has_color;
}	t_app;

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
}	t_bresenham_ctx;

/*
 * FDF
 */
bool		make_fdf(t_app *fdf, char *filename);
void		fdf_destroy_contents(t_app *fdf);
int			fdf_render(t_app *f);
void		fdf_init_edges(t_app *f);
void		fdf_draw_lines(t_app *f);
bool		parse_file(t_app *fdf, char *filename);

/*
 * HANDLERS
 */
int			key_press_handler(int keycode, t_app *fdf);
int			key_release_handler(int keycode, t_app *fdf);
int			button_press_handler(int button, int x, int y, t_app *fdf);
int			button_release_handler(int button, int x, int y, t_app *fdf);
int			motion_handler(int x, int y, t_app *fdf);
void		auto_rotate_update(t_app *fdf);
bool		is_auto_rotate_active(void);

// Event system functions
void		setup_event_bindings(void);
void		handle_key_event(int keycode, unsigned int modifiers, t_app *fdf);
void		event_system_init(t_app *fdf);

/*
 * RENDER
 */
void		render_string(char *str, uint32_t *buf, int x, int y);
void		update_timer(t_renderer *r);

/*
 * PARSE INPUT
 */
bool		parse_chunk(t_parser *p, t_app *fdf, size_t chunk_size);
bool		realloc_all(t_parser *p, t_app *fdf);
bool		parse_color(t_parser *p, size_t chunk_size, size_t *i);
bool		is_delim(char c);
int			skip_delim(char *buf, int end, int i);

/*
 * MATRIX
 */
void		identity_matrix4(float *out);
void		matrix4_multiply(const float *a, const float *b, float *out);
void		matrix4_scalar_multiply(float *m, float scalar);
void		matrix4_rotate_x_abs(float *m, float rads);
void		matrix4_rotate_y_abs(float *m, float rads);
void		matrix4_rotate_z_abs(float *m, float rads);
void		matrix4_translate(
				float *m,
				float delta_x,
				float delta_y,
				float delta_z
				);
void		matrix4_dot_product(
				float *m,
				float *a,
				float *out
				);

/*
 * TRANSFORMATION STACK
 */
void		make_transformation_stack(t_transformation_stack *t);

void		transformation_stack_rotate_x(t_transformation_stack *t, float dx);
void		transformation_stack_rotate_y(t_transformation_stack *t, float dy);
void		transformation_stack_rotate_z(t_transformation_stack *t, float dz);

void		transformation_stack_rview_x(t_transformation_stack *t, float dx);
void		transformation_stack_rview_x2(t_transformation_stack *t, float dx);
void		transformation_stack_rview_z(t_transformation_stack *t, float dz);

void		transformation_stack_isometric(t_transformation_stack *t);
void		transformation_stack_parallel(t_transformation_stack *t);

void		transformation_stack_update(t_transformation_stack *t);
void		transformation_stack_ortho(
				t_transformation_stack *t,
				float x,
				float y,
				float z
				);
void		transformation_stack_zoom(t_transformation_stack *t, int direction);
void		transformation_stack_translate(
				t_transformation_stack *t,
				float dx,
				float dy,
				float dz
				);
void		transformation_stack_pan(
				t_transformation_stack *t,
				float dx,
				float dy
				);
void		transformation_stack_origin(
				t_transformation_stack *t,
				float dx,
				float dy,
				float dz
				);
void		center_model(
				t_transformation_stack *t,
				float width,
				float height,
				float depth
				);

/*
 * PROJECTION CTL
 */
void		make_projection_ctl(
				t_projection_ctl *p,
				float width,
				float height,
				float depth
				);
void		projection_reset_params(t_projection_ctl *p);

/*
 * BRESENHAM
 */
void		bresenham_init(t_bresenham_state *b, t_app *fdf, int i);
void		draw_line_y_major(
				t_bresenham_state *bresenham,
				unsigned int *screen
				);
void		draw_line_x_major(
				t_bresenham_state *bresenham,
				unsigned int *screen
				);

/*
 * UTIL
 */
int			ft_strntoi(int *n, char *str, size_t max);
int			strntohex(uint32_t *n, char *str, char *end);
bool		ft_realloc(void **ptr, size_t *cap, size_t start);
uint32_t	pack_color(t_bresenham_state *b, int step);
uint8_t		*get_glyph(char c);
int			ft_abs(int n);

void	init_mlx_handlers(t_app *f);

/*
 * Color palette helpers (for render/color.c)
 */
extern int			hex_to_color(char *color);
extern void			palette_terrain_2(int *arr, int pos, int z_value);
extern void			palette_gamma_2(int *arr, int pos, int z_value);
extern void			pallete_gamma_random_2(int *arr, int pos, int z_value);
extern void			set_palette_index(int idx, t_app *fdf);

/*
 * TRANSFORMATION FUNCTIONS
 */
void		apply_torus_transformation(t_app *fdf, float major_radius, float minor_radius);
void		apply_cube_transformation(t_app *fdf);
void		apply_pyramid_transformation(t_app *fdf);
void		apply_dna_transformation(t_app *fdf);
void		apply_chips_transformation(t_app *fdf);
void		apply_wave_transformation(t_app *fdf);
void		apply_heart_transformation(t_app *fdf);
void		apply_cone_transformation(t_app *fdf);
void		apply_tube_transformation(t_app *fdf);
void		transition_update(t_app *fdf);
void		transition_start_torus(bool to_torus);
bool		transition_is_active(void);
void		transition_cleanup(void);

/*
 * ANIMATION EFFECTS
 */
void		toggle_parallax_effect(void);
void		render_parallax_effect(t_app *fdf);
void		animate_parallax_grid(void);
bool		is_parallax_active(void);
void		init_parallax_system(void);

/*
 * BACKGROUND AND EFFECTS
 */
void		generate_background(t_app *fdf, int theme_index);
void		generate_stars(t_app *fdf);
void		toggle_stars(void);
bool		are_stars_enabled(void);
int			get_current_background_theme(void);

/*
 * TRACKBALL SYSTEM
 */
void		init_trackball_system(void);
void		trackball_rotate(float q[4], float p1x, float p1y, float p2x, float p2y);
void		add_quats(float q1[4], float q2[4], float dest[4]);
void		quaternion_to_matrix4(float q[4], float m[16]);
void		trackball_start_rotation(int mouse_x, int mouse_y);
void		trackball_update_rotation(int mouse_x, int mouse_y);
void		trackball_end_rotation(void);
void		apply_trackball_to_transform_stack(t_app *fdf);
void		apply_trackball_to_shape_points(t_app *fdf);
void		apply_auto_trackball_rotation(t_app *fdf, float rotation_speed);
bool		is_trackball_active(void);
void		reset_trackball_rotation(void);

/*
 * ENHANCED HANDLERS WITH TRACKBALL
 */
int			trackball_button_press_handler(int button, int x, int y, t_app *fdf);
int			trackball_button_release_handler(int button, int x, int y, t_app *fdf);
int			trackball_motion_handler(int x, int y, t_app *fdf);
int			trackball_key_press_handler(int keycode, t_app *fdf);

/*
 * SHADOW EFFECTS
 */
void		apply_shadow_effects(t_app *fdf, bool depth_shadows, bool ambient_shadows);
void		apply_depth_shadow(t_app *fdf);
void		apply_ambient_shadows(t_app *fdf);
void		toggle_shadow_mode(void);
void		update_shadow_effects(t_app *fdf);
int			get_shadow_mode(void);

/*
 * Z-Perspective Control functions
 */
void init_z_perspective_control(t_app *fdf);
void reduce_z_perspective(t_app *fdf);
void increase_z_perspective(t_app *fdf);
void reset_z_perspective(t_app *fdf);
void set_z_perspective_mode(t_app *fdf, int mode);
float get_z_perspective_scale(void);
void cleanup_z_perspective_control(void);

// Enhanced event handlers
int z_perspective_key_press_handler(int keycode, t_app *fdf);
int z_perspective_key_release_handler(int keycode, t_app *fdf);
bool is_ctrl_pressed(void);
void	init_deltas(t_bresenham_state *b);
void	init_color_delta(t_bresenham_state *b);

#define MAX_EVENT 256

typedef enum e_event
{
	ARROW_UP    = XK_Up,
	ARROW_DOWN  = XK_Down,
	ARROW_LEFT  = XK_Left,
	ARROW_RIGHT = XK_Right,
	W           = XK_w,
	A           = XK_a,
	S           = XK_s,
	D           = XK_d,
	T           = XK_t,
	I           = XK_i,
	P           = XK_p,
	R           = XK_r,
	ESCAPE      = 65307,  // Use direct keycode instead of XK_Escape
	L           = XK_l,
	SPACE_BAR   = XK_space,
	MOUSE_RIGHT = 0x1001,
	MOUSE_LEFT  = 0x1002,
	MOUSE_SCROLL = 0x1003,
	ONE         = XK_1,
	TWO         = XK_2,
	THREE       = XK_3,
	FOUR        = XK_4,
	FIVE        = XK_5,
	SIX         = XK_6,
	SEVEN       = XK_7,
	EIGHT       = XK_8,
	NINE        = XK_9,
	G			= XK_g,  // Change from XK_G to XK_g (lowercase)
}				t_event;

// Composite event key for key+modifier combinations
typedef struct s_event_key
{
	int keycode;
	unsigned int modifiers;
} t_event_key;

// Handler type for composite key events with keycode context
typedef void (*t_event_fn)(t_app*, int keycode, void*);

// Unified event binding (for both plain and combo events)
typedef struct s_event_binding {
	t_event_key key;
	t_event_fn handler;
} t_event_binding;

#define EVENT_BINDINGS_MAX 512

// Event binding registration and lookup
void register_event_binding(int keycode, unsigned int modifiers, t_event_fn handler);
t_event_fn find_event_handler(int keycode, unsigned int modifiers);

// Global state declarations
extern bool g_auto_rotate;

// Movement helper functions (not event handlers)
void		move_forward(t_app *fdf, float amount);
void		move_backward(t_app *fdf, float amount);
void		rotate_up(t_app *fdf, float angle);
void		rotate_down(t_app *fdf, float angle);
void		rotate_left(t_app *fdf, float angle);
void		rotate_right(t_app *fdf, float angle);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    move_up(t_app *fdf, int keycode, void *data);
void    move_down(t_app *fdf, int keycode, void *data);
void    move_left(t_app *fdf, int keycode, void *data);
void    move_right(t_app *fdf, int keycode, void *data);
void    rotate_up_handler(t_app *fdf, int keycode, void *data);
void    rotate_down_handler(t_app *fdf, int keycode, void *data);
void    rotate_left_handler(t_app *fdf, int keycode, void *data);
void    rotate_right_handler(t_app *fdf, int keycode, void *data);
void    zoom_in(t_app *fdf, int keycode, void *data);
void    zoom_out(t_app *fdf, int keycode, void *data);
void    projection_iso(t_app *fdf, int keycode, void *data);
void    projection_fly(t_app *fdf, int keycode, void *data);
void    ch_shape(t_app *fdf, int keycode, void *data);
void    exit_prog(t_app *fdf, int keycode, void *data);
void    reset_state(t_app *fdf, int keycode, void *data);
void    project_iso(t_app *fdf, int keycode, void *data);
void    mouse_right(t_app *fdf, int keycode, void *data);
void    mouse_left(t_app *fdf, int keycode, void *data);
void    scroll_mouse(t_app *fdf, int keycode, void *data);
void    z_perspective_ctrl(t_app *fdf, int keycode, void *data);
void    auto_rotate(t_app *fdf, int keycode, void *data);

// Color palette handlers for keys 1-9
void    palette_1_handler(t_app *fdf, int keycode, void *data);
void    palette_2_handler(t_app *fdf, int keycode, void *data);
void    palette_3_handler(t_app *fdf, int keycode, void *data);
void    palette_4_handler(t_app *fdf, int keycode, void *data);
void    palette_5_handler(t_app *fdf, int keycode, void *data);
void    palette_6_handler(t_app *fdf, int keycode, void *data);
void    palette_7_handler(t_app *fdf, int keycode, void *data);
void    palette_8_handler(t_app *fdf, int keycode, void *data);
void    palette_9_handler(t_app *fdf, int keycode, void *data);

/*
 * PARTICLE SYSTEM
 */
void		transition_start_particles(bool to_particles);
bool		particles_is_active(void);
void		particles_cleanup(void);
void		particles_update(t_app *fdf);
void		apply_snow_particles(t_app *fdf);
void		apply_rain_particles(t_app *fdf);
void		apply_fire_particles(t_app *fdf);
void		apply_sparks_particles(t_app *fdf);
void		apply_stars_particles(t_app *fdf);
void		apply_bubbles_particles(t_app *fdf);
void		apply_dust_particles(t_app *fdf);
void		apply_smoke_particles(t_app *fdf);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    ch_particules(t_app *fdf, int keycode, void *data);

#endif
