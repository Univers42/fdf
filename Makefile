# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 23:01:30 by dlesieur          #+#    #+#              #
#    Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = fdf
CC      = cc

# Parallel by default; per-target overridable with `make -j1`.
MAKEFLAGS += -j$(shell nproc)

SRC_DIR = sources
OBJ_DIR = object

LIBFT_DIR = include/libft
LIBFT_A   = $(LIBFT_DIR)/build/lib/libft.a
MLX_DIR   = include/lib/minilibx-linux
MLX_A     = $(MLX_DIR)/libmlx.a

INCLUDES = -Iinclude -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR)

WARN = -Wall -Wextra -Werror
# Release: native vectorization + LTO + fast float math (no NaN/inf checks in
# this codebase, verified). Override OPT for other modes (see debug target).
OPT ?= -O3 -march=native -flto=auto -ffast-math -funroll-loops
CFLAGS  = $(WARN) $(OPT) -MMD -MP $(INCLUDES)
LDFLAGS = $(OPT)
LDLIBS  = $(LIBFT_A) $(MLX_A) -lX11 -lXext -lm

SRCS := $(shell find $(SRC_DIR) -name '*.c' | sort)
OBJS  = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS  = $(OBJS:.o=.d)

all: $(NAME)

bonus: all

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

debug: fclean
	$(MAKE) OPT="-O0 -g3 -fsanitize=address,undefined" $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

norminette:
	find sources include -path "$(MLX_DIR)" -prune -o \( -name "*.c" -o -name "*.h" \) -print | grep -v "^include/libft" | xargs norminette

.PHONY: all bonus clean fclean re debug norminette
