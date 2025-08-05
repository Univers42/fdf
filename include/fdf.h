/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:51:48 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/05 18:17:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 2920
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 2000
# endif

# if WINDOW_HEIGHT * WINDOW_WIDTH < 32
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
	struct timespec	last_tick;
	struct timespec	tick;
	struct timespec	text_tick;
	struct timespec	temp;
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
int			button_press_handler(int button, int x, int y, t_app *fdf);
int			button_release_handler(int button, int x, int y, t_app *fdf);
int			motion_handler(int x, int y, t_app *fdf);
void		auto_rotate_update(t_app *fdf);
bool		is_auto_rotate_active(void);

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
#endif
