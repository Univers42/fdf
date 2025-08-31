# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 23:01:30 by dlesieur          #+#    #+#              #
#    Updated: 2025/08/31 14:19:17 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#verify dependencies

NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -O3
#CFLAGS += -fsanitize=address
PROJECT_DIR = $(shell pwd)
SRC_DIR = $(PROJECT_DIR)/sources
INCLUDE_DIR=$(PROJECT_DIR)/include
OBJ_DIR = $(PROJECT_DIR)/object

# Use wildcard to include all .c files in sources and its subdirectories
SRC_DIR = sources
ALGORITHMS_DIR = $(SRC_DIR)/algorithms
ANIMATION_DIR = $(SRC_DIR)/animation
CORE_DIR = $(SRC_DIR)/core
EVENTS_DIR = $(SRC_DIR)/events
STUB_DIR = $(EVENTS_DIR)/stub_event
HELPERS_DIR = $(SRC_DIR)/helpers
PARSER_DIR = $(SRC_DIR)/parser
RENDER_DIR = $(SRC_DIR)/render
BACKGROUND_DIR = $(RENDER_DIR)/background
PARTICLES_DIR = $(RENDER_DIR)/particles
TEXTURES_DIR = $(RENDER_DIR)/textures
THEME_DIR = $(RENDER_DIR)/theme
WRITE_DIR = $(RENDER_DIR)/writer
TRACKBALL_DIR = $(SRC_DIR)/trackball
TRANSFORM_DIR = $(SRC_DIR)/transform
EFFECTS_DIR = $(TRANSFORM_DIR)/effects
PROJECTION_DIR = $(TRANSFORM_DIR)/projection
SHAPES_DIR = $(TRANSFORM_DIR)/shapes
UTILS_DIR = $(SRC_DIR)/utils

#COMPLETE
SRCS =	$(ALGORITHMS_DIR)/bresenham.c \
    	$(ALGORITHMS_DIR)/fdf_draw_lines.c \
    	$(ALGORITHMS_DIR)/matrix4_vector.c \
    	$(ALGORITHMS_DIR)/matrix4.c

#COMPLETE
SRCS += $(ANIMATION_DIR)/dancing_system.c \
        $(ANIMATION_DIR)/dynamic_background_system.c \
        $(ANIMATION_DIR)/helper_background.c \
        $(ANIMATION_DIR)/helper_dance.c \
        $(ANIMATION_DIR)/helper_heart.c \
        $(ANIMATION_DIR)/helper_object.c \
        $(ANIMATION_DIR)/helper_particle1.c \
        $(ANIMATION_DIR)/helper_particle2.c \
        $(ANIMATION_DIR)/helper_particule3.c \
        $(ANIMATION_DIR)/helper_texture.c \
        $(ANIMATION_DIR)/helper_transition.c \
        $(ANIMATION_DIR)/helper_transition2.c \
        $(ANIMATION_DIR)/helper_transition3.c \
        $(ANIMATION_DIR)/helpers_dance.c \
        $(ANIMATION_DIR)/object_effects.c \
        $(ANIMATION_DIR)/particle_system.c \
        $(ANIMATION_DIR)/pos_cone.c \
        $(ANIMATION_DIR)/pos_dna.c \
        $(ANIMATION_DIR)/pos_heart.c \
        $(ANIMATION_DIR)/pos_tube.c \
        $(ANIMATION_DIR)/position_shape1.c \
        $(ANIMATION_DIR)/position_shape2.c \
        $(ANIMATION_DIR)/position_shape3.c \
        $(ANIMATION_DIR)/texture_system.c \
        $(ANIMATION_DIR)/transition_system.c

#COMPLETE
SRCS += $(CORE_DIR)/fdf_init_edges.c \
		$(CORE_DIR)/fdf.c \
		$(CORE_DIR)/init_bresenham.c \
		$(CORE_DIR)/main.c
#COMPLETE
SRCS += $(EVENTS_DIR)/handlers.c \
		$(EVENTS_DIR)/handle_events.c \
		$(EVENTS_DIR)/helper_event2.c \
		$(EVENTS_DIR)/helpers_event.c
# COMPLETE
SRCS += $(STUB_DIR)/close_cross.c \
		$(STUB_DIR)/stub_apply1.c \
		$(STUB_DIR)/stub_apply2.c \
		$(STUB_DIR)/stub_apply3.c \
		$(STUB_DIR)/stub_camera_projection.c \
		$(STUB_DIR)/stub_mouse.c \
		$(STUB_DIR)/stub_move_camera.c \
		$(STUB_DIR)/stub_move_orthodox.c \
		$(STUB_DIR)/stub_others.c \
		$(STUB_DIR)/stub_reset.c \
		$(STUB_DIR)/stub_rotate.c \
		$(STUB_DIR)/stub_rotate_internal.c \
		$(STUB_DIR)/stub_theme.c \
		$(STUB_DIR)/stub_theme2.c \
		$(STUB_DIR)/stub_transformation.c

#COMPLETE
SRCS += $(HELPERS_DIR)/cleanup.c \
		$(HELPERS_DIR)/cleanup2.c \
		$(HELPERS_DIR)/frees.c \
		$(HELPERS_DIR)/grow_buf.c \
		$(HELPERS_DIR)/lerp.c \
		$(HELPERS_DIR)/singletons.c \
		$(HELPERS_DIR)/singletons2.c \
		$(HELPERS_DIR)/singletons3.c

#COMPLETE
SRCS +=	$(PARSER_DIR)/helper2.c \
		$(PARSER_DIR)/helpers.c \
		$(PARSER_DIR)/parse_chunk.c \
		$(PARSER_DIR)/parse_utils.c \
		$(PARSER_DIR)/parse.c
#COMPLETE
SRCS += $(RENDER_DIR)/render.c
#COMPLETE
SRCS += $(BACKGROUND_DIR)/aurora_waves.c \
		$(BACKGROUND_DIR)/background.c \
		$(BACKGROUND_DIR)/cosmic_nebula.c \
		$(BACKGROUND_DIR)/dramatic_clouds.c \
		$(BACKGROUND_DIR)/electric_storm.c \
		$(BACKGROUND_DIR)/epileptic.c \
		$(BACKGROUND_DIR)/fire_plasma.c \
		$(BACKGROUND_DIR)/generate_stars.c \
		$(BACKGROUND_DIR)/helper_storm.c \
		$(BACKGROUND_DIR)/liquid_metal.c \
		$(BACKGROUND_DIR)/matrix_rain.c \
		$(BACKGROUND_DIR)/rainbow_vortex.c\
		$(BACKGROUND_DIR)/vibrant_grad.c \
		$(BACKGROUND_DIR)/water_ripples.c

#COMPLETE
SRCS += $(PARTICLES_DIR)/bubbles.c \
		$(PARTICLES_DIR)/dust.c \
		$(PARTICLES_DIR)/fire.c\
		$(PARTICLES_DIR)/rain.c\
		$(PARTICLES_DIR)/smoke.c\
		$(PARTICLES_DIR)/snow.c\
		$(PARTICLES_DIR)/sparks.c\
		$(PARTICLES_DIR)/stars.c

#COMPLETE
SRCS += $(TEXTURES_DIR)/apply_circuit_texture.c \
		$(TEXTURES_DIR)/blend_color.c\
		$(TEXTURES_DIR)/brick_texture.c\
		$(TEXTURES_DIR)/carbon_fiber.c\
		$(TEXTURES_DIR)/checkerboard.c\
		$(TEXTURES_DIR)/hexagon_texture.c\
		$(TEXTURES_DIR)/marble_texture.c\
		$(TEXTURES_DIR)/metal_brushed.c\
		$(TEXTURES_DIR)/plasma_texture.c\
		$(TEXTURES_DIR)/scales_textures.c\
		$(TEXTURES_DIR)/stripes.c\
		$(TEXTURES_DIR)/texture_color.c\
		$(TEXTURES_DIR)/wood_grain.c

#COMPLETE
SRCS += $(THEME_DIR)/color_helpers.c\
		$(THEME_DIR)/color_pack.c\
		$(THEME_DIR)/palette_defs.c\
		$(THEME_DIR)/palette_integration.c\
		$(THEME_DIR)/palette_system.c\
		$(THEME_DIR)/theme_presets_part1.c\
		$(THEME_DIR)/theme_presets_part2.c

#COMPLETE
SRCS += $(WRITE_DIR)/font.c \
		$(WRITE_DIR)/render_string.c

#COMPLETE
SRCS += $(TRACKBALL_DIR)/helpers.c\
		$(TRACKBALL_DIR)/trackball_apply.c\
		$(TRACKBALL_DIR)/trackball_handlers.c\
		$(TRACKBALL_DIR)/trackball_integration.c

#COMPLETE
SRCS += $(TRANSFORM_DIR)/helper_z1.c \
		$(TRANSFORM_DIR)/helper_z2.c\
		$(TRANSFORM_DIR)/helpers.c\
		$(TRANSFORM_DIR)/transformation_rotation.c\
		$(TRANSFORM_DIR)/transformation_update.c\
		$(TRANSFORM_DIR)/transformation.c\
		$(TRANSFORM_DIR)/z_perspective_control.c

#COMPLETE
SRCS += $(EFFECTS_DIR)/bounce.c\
		$(EFFECTS_DIR)/contract.c\
		$(EFFECTS_DIR)/distortion_effect.c\
		$(EFFECTS_DIR)/expand_contract.c\
		$(EFFECTS_DIR)/explosion_effect.c \
		$(EFFECTS_DIR)/figure_eight.c\
		$(EFFECTS_DIR)/fold_effect.c\
		$(EFFECTS_DIR)/helpers_shadow.c\
		$(EFFECTS_DIR)/pulse.c\
		$(EFFECTS_DIR)/shadow_effects.c\
		$(EFFECTS_DIR)/shadow_helpers.c\
		$(EFFECTS_DIR)/spin.c\
		$(EFFECTS_DIR)/spiral_twist_effect.c\
		$(EFFECTS_DIR)/twist.c\
		$(EFFECTS_DIR)/vertex_magnet.c\
		$(EFFECTS_DIR)/vertex_scatter_effect.c\
		$(EFFECTS_DIR)/vertex_wave.c\
		$(EFFECTS_DIR)/wave_motion.c\
		$(EFFECTS_DIR)/wobble.c

#COMPLETE
SRCS += $(PROJECTION_DIR)/projection_ctl.c\
		$(PROJECTION_DIR)/transformation_projection.c\
		$(PROJECTION_DIR)/transformation_rview.c

#COMPLETE
SRCS += $(SHAPES_DIR)/helper_cube.c\
		$(SHAPES_DIR)/inline_helper.c\
		$(SHAPES_DIR)/transform_chips.c\
		$(SHAPES_DIR)/transform_cube.c\
		$(SHAPES_DIR)/transform_dna.c\
		$(SHAPES_DIR)/transform_heart.c\
		$(SHAPES_DIR)/transform_pyramid.c\
		$(SHAPES_DIR)/transform_sphere.c\
		$(SHAPES_DIR)/transform_toro.c\
		$(SHAPES_DIR)/transform_tube.c\
		$(SHAPES_DIR)/transform_wave.c

#COMPLETE
SRCS += $(UTILS_DIR)/colors.c


#SRCS = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))

LIBFT_DIR = $(INCLUDE_DIR)/lib
MLX_DIR = $(LIBFT_DIR)/minilibx-linux

LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_A = $(MLX_DIR)/libmlx.a

# Find all unique directories containing .h files in the project, always include root dir
HEADER_DIRS := $(shell find $(INCLUDE_DIR) -type f -name '*.h' -exec dirname {} \; | sort -u)
INCLUDE_FLAGS := $(foreach dir,$(HEADER_DIRS),-I$(dir))

CFLAGS += $(INCLUDE_FLAGS)

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) $(MLX_A) -lX11 -lXext -lm

$(LIBFT_A) $(MLX_A):
	$(MAKE) -C $(LIBFT_DIR) all

# Pattern rule to build .o files in object/ from .c files in sources/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

norminette:
	find . -path "./include/lib/minilibx-linux" -prune -o -name "*.c" -exec norminette {} +

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re