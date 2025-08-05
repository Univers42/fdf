#verify dependencies

NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -O3
PROJECT_DIR = $(shell pwd)
SRC_DIR = $(PROJECT_DIR)/sources
INCLUDE_DIR=$(PROJECT_DIR)/include
OBJ_DIR = $(PROJECT_DIR)/object

# Use wildcard to include all .c files in sources and its subdirectories
SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))

LIBFT_DIR = $(INCLUDE_DIR)/libft
MLX_DIR = $(LIBFT_DIR)/minilibx-linux

LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_A = $(MLX_DIR)/libmlx.a

# Find all unique directories containing .h files in the project, always include root dir
HEADER_DIRS := $(shell find $(INCLUDE_DIR) -type f -name '*.h' -exec dirname {} \; | sort -u)
INCLUDE_FLAGS := $(foreach dir,$(HEADER_DIRS),-I$(dir))

CFLAGS += $(INCLUDE_FLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
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

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re