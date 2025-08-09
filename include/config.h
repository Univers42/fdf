/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:33:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 02:07:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/**
Can adapt the all the macro using this command when compiling in terminal
-D<MACRO_NAME>=<value>
*/

// Can set the size of the win either height or width
# ifndef WIN_WIDTH
#  define WIN_WIDTH 2920
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 2000
# endif

// Check that the new value are not under 32 otherwise fallback value
# if WIN_HEIGHT * WIN_WIDTH < 32
#  error "window height * window width must be greater than 32"
#  undef WIN_HEIGHT
#  undef WIN_WIDTH
#  define WIN_HEIGHT	32
#  define WIN_WIDTH		32
# endif


#define PARTICLE_TRANSITION_FRAMES	45
#define PARTICLE_COUNT				9
#define MAX_PARTICLES				150
#define PARTICLE_LIFETIME			300
#define DYNAMIC_BG_COUNT			12
#define WAVE_FREQUENCY				0.08f
#define OBJECT_EFFECT_COUNT			10
#define DANCE_MOVE_COUNT        	8
#define DANCE_TRANSITION_FRAMES 	120
#define DANCE_HOLD_FRAMES       	180
#define TEXTURE_COUNT				12

#define MAX_EVENT 256
#define EVENT_BINDINGS_MAX 512

#define Z_SCALE_STEP 0.1f
#define MAX_Z_LIMIT 500.0f
#define MIN_Z_LIMIT 0.0f
#define CONVERGENCE_THRESHOLD 500.0f
#define CONVERGENCE_FACTOR 0.7f

#define ROTATE_FACTOR 0.03f
#define MOVE_FACTOR   2.0f
#define AUTO_ROTATE_SPEED 0.01f // Slower auto-rotation

#define MAX_KEYCODE 70000  // Increased to handle X11 keycodes
#define MODIFIER_COMBO_COUNT 8 // 3 bits: Shift, Ctrl, Alt

#define FONT_CHAR_0      "\x3E\x63\x73\x7B\x6F\x67\x3E\x00"
#define FONT_CHAR_1      "\x0C\x0E\x0C\x0C\x0C\x0C\x3F\x00"
#define FONT_CHAR_2      "\x1E\x33\x30\x1C\x06\x33\x3F\x00"
#define FONT_CHAR_3      "\x1E\x33\x30\x1C\x30\x33\x1E\x00"
#define FONT_CHAR_4      "\x38\x3C\x36\x33\x7F\x30\x78\x00"
#define FONT_CHAR_5      "\x3F\x03\x1F\x30\x30\x33\x1E\x00"
#define FONT_CHAR_6      "\x1C\x06\x03\x1F\x33\x33\x1E\x00"
#define FONT_CHAR_7      "\x3F\x33\x30\x18\x0C\x0C\x0C\x00"
#define FONT_CHAR_8      "\x1E\x33\x33\x1E\x33\x33\x1E\x00"
#define FONT_CHAR_9      "\x1E\x33\x33\x3E\x30\x18\x0E\x00"
#define FONT_CHAR_SPACE  "\x00\x00\x00\x00\x00\x00\x00\x00"
#define FONT_CHAR_F      "\x7F\x46\x16\x1E\x16\x06\x0F\x00"
#define FONT_CHAR_P      "\x00\x00\x3B\x66\x66\x3E\x06\x0F"
#define FONT_CHAR_S      "\x00\x00\x3E\x03\x1E\x30\x1F\x00"
#define FONT_CHAR_COLON  "\x00\x0C\x0C\x00\x00\x0C\x0C\x00"
#define FONT_CHAR_PERIOD "\x00\x00\x00\x00\x00\x0C\x0C\x00"

/**
	* ENUMS
 */
typedef enum e_texture_type {
	TEXTURE_NONE = 0,
	TEXTURE_CHECKERBOARD = 1,
	TEXTURE_STRIPES = 2,
	TEXTURE_WOOD_GRAIN = 3,
	TEXTURE_METAL_BRUSHED = 4,
	TEXTURE_CARBON_FIBER = 5,
	TEXTURE_MARBLE = 6,
	TEXTURE_BRICK = 7,
	TEXTURE_CIRCUIT_BOARD = 8,
	TEXTURE_SCALES = 9,
	TEXTURE_HEXAGON = 10,
	TEXTURE_PLASMA = 11
}	t_texture_type;

typedef enum e_object_effect_type {
	OBJ_EFFECT_NONE = 0,
	OBJ_EFFECT_VERTEX_WAVE = 1,
	OBJ_EFFECT_GEOMETRIC_PULSE = 2,
	OBJ_EFFECT_VERTEX_EXPLOSION = 3,
	OBJ_EFFECT_SPIRAL_TWIST = 4,
	OBJ_EFFECT_DEPTH_DISTORTION = 5,
	OBJ_EFFECT_VERTEX_MAGNET = 6,
	OBJ_EFFECT_GEOMETRIC_FOLD = 7,
	OBJ_EFFECT_HEIGHT_OSCILLATION = 8,
	OBJ_EFFECT_VERTEX_SCATTER = 9
}	t_object_effect_type;

typedef enum e_dynamic_bg_type {
	DYNAMIC_BG_STATIC = 0,
	DYNAMIC_BG_VIBRANT_GRADIENT = 1,
	DYNAMIC_BG_DRAMATIC_CLOUDS = 2,
	DYNAMIC_BG_EPILEPTIC_FLASH = 3,
	DYNAMIC_BG_WATER_RIPPLES = 4,
	DYNAMIC_BG_FIRE_PLASMA = 5,
	DYNAMIC_BG_MATRIX_RAIN = 6,
	DYNAMIC_BG_AURORA_WAVES = 7,
	DYNAMIC_BG_COSMIC_NEBULA = 8,
	DYNAMIC_BG_ELECTRIC_STORM = 9,
	DYNAMIC_BG_LIQUID_METAL = 10,
	DYNAMIC_BG_RAINBOW_VORTEX = 11
}	t_dynamic_bg_type;

typedef enum e_shape_type {
	SHAPE_ORIGINAL,
	SHAPE_TORUS,
	SHAPE_SPHERE,
	SHAPE_CUBE,
	SHAPE_PYRAMID,
	SHAPE_DNA,
	SHAPE_CHIPS,
	SHAPE_WAVE,
	SHAPE_HEART,
	SHAPE_CONE,
	SHAPE_TUBE,
	SHAPE_COUNT
}	t_shape_type;

typedef enum e_dance_move {
	DANCE_NONE = 0,
	DANCE_SPIN = 1,
	DANCE_BOUNCE = 2,
	DANCE_WAVE_MOTION = 3,
	DANCE_TWIST = 4,
	DANCE_EXPAND_CONTRACT = 5,
	DANCE_FIGURE_EIGHT = 6,
	DANCE_WOBBLE = 7
} t_dance_move;

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

typedef enum e_input_state
{
	INPUT_STATE_IDLE,
	INPUT_STATE_DRAGGING,
	INPUT_STATE_ROTATING,
}	t_input_state;

typedef enum e_particle_type {
	PARTICLE_NONE = 0,
	PARTICLE_SNOW = 1,
	PARTICLE_RAIN = 2,
	PARTICLE_FIRE = 3,
	PARTICLE_SPARKS = 4,
	PARTICLE_STARS = 5,
	PARTICLE_BUBBLES = 6,
	PARTICLE_DUST = 7,
	PARTICLE_SMOKE = 8
} t_particle_type;



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
	ESCAPE      = 65307,
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
	G           = XK_g,
	H           = XK_h,
	Z_KEY			= XK_z,
	B			= XK_b,
	V			= XK_v
}				t_event;
#endif