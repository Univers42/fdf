/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:51:48 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/08 00:30:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "config.h"
#include "ds.h"

extern t_dance_system g_dance;
extern  t_object_effects_system g_obj_effects;
extern t_particle_transition g_particle_system ;
extern t_dynamic_bg_system g_dynamic_bg;
extern t_texture_system g_texture;
extern t_trackball_shape_state g_trackball_state;
/*
 * FDF
 */
bool		make_fdf(t_app *fdf, char *filename);
void		fdf_destroy_contents(t_app *fdf);
int			fdf_render(t_app *f);
void		fdf_init_edges(t_app *fdf);
void		fdf_draw_lines(t_app *fdf);
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
bool		is_auto_rotate_active(t_app *fdf);

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
void		matrix4_translate(float *m, float delta_x, float delta_y, float delta_z);
void		matrix4_dot_product(float *m, float *a, float *out);

/*
 * TRANSFORMATION STACK
 */
void		make_trans_stack(t_trans_stack *t);

void		trans_stack_rotate_x(t_trans_stack *t, float dx);
void		trans_stack_rotate_y(t_trans_stack *t, float dy);
void		trans_stack_rotate_z(t_trans_stack *t, float dz);

void		trans_stack_rview_x(t_trans_stack *t, float dx);
void		trans_stack_rview_x2(t_trans_stack *t, float dx);
void		trans_stack_rview_z(t_trans_stack *t, float dz);

void		trans_stack_isometric(t_trans_stack *t);
void		trans_stack_parallel(t_trans_stack *t);

void		trans_stack_update(t_trans_stack *t);
void		trans_stack_ortho(t_trans_stack *t, float x, float y, float z);
void		trans_stack_zoom(t_trans_stack *t, int direction);
void		trans_stack_translate(t_trans_stack *t, float dx, float dy, float dz);
void		trans_stack_pan(t_trans_stack *t, float dx, float dy);
void		trans_stack_origin(t_trans_stack *t, float dx, float dy, float dz);
void		center_model(t_trans_stack *t, float width, float height, float depth);

/*
 * PROJECTION CTL
 */
void		make_projection_ctl(t_projection_ctl *p, float width, float height, float depth);
void		projection_reset_params(t_projection_ctl *p);

/*
 * BRESENHAM
 */
void		bresenham_init(t_bresenham_state *b, t_app *fdf, int i);
void		draw_line_y_major(t_bresenham_state *bresenham, unsigned int *screen);
void		draw_line_x_major(t_bresenham_state *bresenham, unsigned int *screen);

/*
 * UTIL
 */
int			ft_strntoi(int *n, char *str, size_t max);
int			strntohex(uint32_t *n, char *str, char *end);
bool		ft_realloc(void **ptr, size_t *cap, size_t start);
uint32_t	pack_color(t_bresenham_state *b, int step);
uint8_t		*get_glyph(char c);
int			ft_abs(int n);
void		init_mlx_handlers(t_app *f);

/*
 * Color palette helpers
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
void		apply_cube_face_0_1(t_meta_shape *s, t_app *fdf);
void		apply_cube_face_2_3(t_meta_shape *s, t_app *fdf);
void		apply_cube_face_4_5(t_meta_shape *s, t_app *fdf);
float	get_dna_norm_y(t_app *fdf, t_meta_shape *s);
int	get_dna_index(t_app *fdf, t_meta_shape *s);
float	calc_heart_upper_lobes(float norm_x, float norm_y);
float	get_tube_angle(int x, int width);

float	get_tube_radius(t_app *fdf, t_meta_shape *s, float max_radius);
/*
 * ANIMATION EFFECTS
 */
void		toggle_parallax_effect(void);
void		render_parallax_effect(t_app *fdf);
void		animate_parallax_grid(void);
bool		is_parallax_active(void);
void		init_parallax_system(void);

void	check_projection(t_projection_ctl *p);
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
void		init_z_perspective_control(t_app *fdf);
void		reduce_z_perspective(t_app *fdf);
void		increase_z_perspective(t_app *fdf);
void		reset_z_perspective(t_app *fdf);
void		set_z_perspective_mode(t_app *fdf, int mode);
float		get_z_perspective_scale(void);
void		cleanup_z_perspective_control(void);

// Enhanced event handlers
int			z_perspective_key_press_handler(int keycode, t_app *fdf);
int			z_perspective_key_release_handler(int keycode, t_app *fdf);
bool		is_ctrl_pressed(void);
void		init_deltas(t_bresenham_state *b);
void		init_color_delta(t_bresenham_state *b);

// Event binding registration and lookup
void register_event_binding(int keycode, unsigned int modifiers, t_event_fn handler);
t_event_fn find_event_handler(int keycode, unsigned int modifiers);

// Global state declarations

// Movement helper functions (not event handlers)
void		move_forward(t_app *fdf, float amount);
void		move_backward(t_app *fdf, float amount);
void		rotate_up(t_app *fdf, float angle);
void		rotate_down(t_app *fdf, float angle);
void		rotate_left(t_app *fdf, float angle);
void		rotate_right(t_app *fdf, float angle);
void		move_left_internal(t_app *fdf, float amount);
void		move_right_internal(t_app *fdf, float amount);

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

/*
 * EFFECTS SYSTEM
 */
void		transition_start_effects(bool to_effects);
bool		effects_is_active(void);
void		effects_cleanup(void);
void		effects_update(t_app *fdf);

/*
 * OBJECT EFFECTS SYSTEM - Effects that modify the 3D object itself
 */
void		transition_start_object_effects(bool to_effects);
bool		object_effects_is_active(void);
void		object_effects_cleanup(void);
void		object_effects_update(t_app *fdf);
void		set_object_effect_intensity(float intensity);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    ch_effect(t_app *fdf, int keycode, void *data);

/*
 * ULTIMATE DANCING SYSTEM - Make your 3D objects dance!
 */
void		dance_system_update(t_app *fdf);
void		dance_system_toggle(void);
bool		dance_system_is_active(void);
void		dance_system_cleanup(void);
void		dance_system_set_rhythm(float multiplier);
void		dance_system_toggle_auto_sequence(void);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    dance_toggle_handler(t_app *fdf, int keycode, void *data);

/*
 * ULTIMATE DYNAMIC BACKGROUND SYSTEM - Spectacular animated backgrounds!
 */
void		dynamic_background_update(t_app *fdf);
void		dynamic_background_toggle(void);
bool		dynamic_background_is_active(void);
void		dynamic_background_set_speed(float speed);
void		dynamic_background_cleanup(void);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    dynamic_background_toggle_handler(t_app *fdf, int keycode, void *data);

void		apply_stars_particles(t_app *fdf);
void		apply_bubbles_particles(t_app *fdf);
void		apply_dust_particles(t_app *fdf);
void		apply_smoke_particles(t_app *fdf);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    ch_particules(t_app *fdf, int keycode, void *data);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    ch_effect(t_app *fdf, int keycode, void *data);

/*
 * OBJECT EFFECTS SYSTEM - Effects that modify the 3D object itself
 */
void		transition_start_object_effects(bool to_effects);
bool		object_effects_is_active(void);
void		object_effects_cleanup(void);
void		object_effects_update(t_app *fdf);
void		set_object_effect_intensity(float intensity);

/*
 * ULTIMATE TEXTURE SYSTEM - Apply realistic textures to 3D objects!
 */
void		texture_system_update(t_app *fdf);
void		texture_system_toggle(void);
bool		texture_system_is_active(void);
void		texture_system_set_scale(float scale);
void		texture_system_set_speed(float speed);
void		texture_system_cleanup(void);

//SWITCH EVENTS - Updated signatures with keycode parameter
void    texture_toggle_handler(t_app *fdf, int keycode, void *data);

/*
 * PARTICLES
 */

void    particle_snow(t_particle *p);
void	particle_rain(t_particle *p);
void	particle_fire(t_particle *p);
void	particle_sparks(t_particle *p);
void	particle_stars(t_particle *p);
void	particle_bubbles(t_particle *p);
void	particle_dust(t_particle *p);
void	particle_smoke(t_particle *p);

/*
	* BACKGROUND
*/
void	apply_matrix_rain_bg(uint32_t *buffer);
void    apply_vibrant_gradient_bg(uint32_t *buffer);
void	apply_epileptic_flash_bg(uint32_t *buffer);
void	apply_water_ripples_bg(uint32_t *buffer);
void	apply_fire_plasma_bg(uint32_t *buffer);
void	apply_aurora_waves_bg(uint32_t *buffer);
void	apply_cosmic_nebula_bg(uint32_t *buffer);
void	apply_electric_storm_bg(uint32_t *buffer);
void	apply_liquid_metal_bg(uint32_t *buffer);
void	apply_rainbow_vortex_bg(uint32_t *buffer);
void apply_dramatic_clouds_bg(uint32_t *buffer);
uint32_t lerp_color(uint32_t c1, uint32_t c2, float t);

/**
 * EFFECTS
*/
void    apply_vertex_wave_effect(t_app *fdf);
// Apply geometric pulse effect - makes the entire object pulse in size
void apply_geometric_pulse_effect(t_app *fdf);
void apply_vertex_explosion_effect(t_app *fdf);
void apply_spiral_twist_effect(t_app *fdf);
void apply_depth_distortion_effect(t_app *fdf);
// Apply vertex magnet effect - attracts vertices to moving points
void apply_vertex_magnet_effect(t_app *fdf);
void apply_geometric_fold_effect(t_app *fdf);
void apply_vertex_scatter_effect(t_app *fdf);
void apply_height_oscillation_effect(t_app *fdf);
void apply_dance_spin(t_app *fdf);
void apply_dance_bounce(t_app *fdf);
void apply_dance_wave_motion(t_app *fdf);
void apply_dance_twist(t_app *fdf);
void apply_dance_expand_contract(t_app *fdf);
void apply_dance_figure_eight(t_app *fdf);
void apply_dance_wobble(t_app *fdf);


/**
*	TEXTURES
*/
void apply_circuit_board_texture(t_app *fdf);
uint32_t    blend_colors(uint32_t base_color, uint32_t texture_color, float blend_factor);
void    apply_brick_texture(t_app *fdf);
void apply_carbon_fiber_texture(t_app *fdf);
void apply_checkerboard_texture(t_app *fdf);
void apply_hexagon_texture(t_app *fdf);
void apply_marble_texture(t_app *fdf);
void apply_metal_brushed_texture(t_app *fdf);
void apply_plasma_texture(t_app *fdf);
void apply_scales_texture(t_app *fdf);
void apply_stripes_texture(t_app *fdf);
void    store_original_texture_colors(t_app *fdf);
void apply_wood_grain_texture(t_app *fdf);

/**
singletons
*/

t_z_perspective	gzperspective(t_z_perspective *set);
/**
z_point
*/
void	set_z_perspective_mode(t_app *fdf, int mode);
float	get_z_perspective_scale(void);
void	reduce_z_perspective(t_app *fdf);
void	increase_z_perspective(t_app *fdf);
void	reset_z_perspective(t_app *fdf);
void	update_z_points(t_app *fdf, t_z_perspective *ctrl);
float	get_target_scale(int mode);
void	update_z_perspective(t_app *fdf, float scale_change);
float	calculate_wobble_component(float freq, float multiplier,
								float scale);
float	calculate_wobble_axis(float freq, float *multipliers,
								float *scales);
float	gcamera_speed(float set);

t_modifier_state		*gmod_state(t_modifier_state *set);
t_event_handler_table	*get_event_handler_table(void);
int						map_keycode(int keycode);
t_keycode_map			*gkeycode(void);
void	init_mlx_handlers(t_app *f);
void	setup_event_bindings(void);
void	handle_key_event(int keycode, unsigned int modifiers, t_app *fdf);
void	toggle_effects(t_app *fdf, int keycode, void *data);
void	register_event_binding(int keycode, unsigned int modifiers,
		t_event_fn handler);
t_event_fn	find_event_handler(int keycode, unsigned int modifiers);
int	modifier_index(unsigned int mods);
void	setup_movement_bindings(void);
void	setup_control_bindings(void);
void	setup_palette_bindings(void);
void	setup_feature_toggle_bindings(void);

#endif