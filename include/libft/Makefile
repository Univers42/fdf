# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 12:30:42 by dlesieur          #+#    #+#              #
#    Updated: 2025/08/09 20:14:16 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Static MAKEFILE includes
include build/colors.mk
include build/common.mk

define build_lib
	$(MAKE) -C $(1) $(2)
endef

define trans_remove_c
	find . -type f -name "main.c" -exec sh -c 'mv "$$1" "$${1%.c}.bak"' _ {} \;
endef

define trans_add_c
	find . -type f -name "main.bak" -exec sh -c 'mv "$$1" "$${1%.bak}.c"' _ {} \;
endef

# MAIN ?=

# Library name
NAME = libft.a
MINILIBX_DIR ?= minilibx-linux
MINILIBX_LIB ?= $(MINILIBX_DIR)/libmlx.a
MLX_ALT_LIB ?= $(MINILIBX_DIR)/mlx.a
MLX_FLAGS ?=

# Detect availability of MiniLibX (directory + makefile)
MLX_ENABLED := 0
ifneq ($(wildcard $(MINILIBX_DIR)),)
ifneq ($(or $(wildcard $(MINILIBX_DIR)/Makefile),$(wildcard $(MINILIBX_DIR)/makefile)),)
MLX_ENABLED := 1
endif
endif

# Tag directories that depend on MiniLibX
MLX_TAG_DIRS ?= classes/render/window classes/render/inputHandler classes/render/event

# Allow users to force-skip directories externally
SKIP_DIRS ?=
ifeq ($(MLX_ENABLED),0)
SKIP_DIRS += $(MLX_TAG_DIRS)
endif

# Directories
DATA_STRUCTURES = 	data_structures/queue data_structures/circular_linked_list data_structures/doubly_linked_list\
					data_structures/lists data_structures/vector classes/render/map classes/render/window classes/render/inputHandler classes/render/point classes/render/line classes/trace/error \
					stdlib/arena stdlib/pool stdlib/slab classes/render/event \
					math/geometry math/geometry/draw math/geometry/effects math/geometry/matrices/ math/geometry/move math/geometry/quaternion \
					math/geometry/shapes math/geometry/view math/algebra

# classes classes/render classes/render/window classes/render/inputHandler classes/render/point/ classes/render/camera
SRC_DIRS = ctype debug $(DATA_STRUCTURES) math memory render stdio stdio/ft_printf/src stdlib strings sort classes/render/inputHandler

# Compute effective source directories after excluding tagged ones
SRC_DIRS_EFF := $(filter-out $(SKIP_DIRS),$(SRC_DIRS))

# Source files from all directories including ft_printf and gnl
SRCS = $(foreach dir,$(SRC_DIRS_EFF),$(wildcard $(dir)/*.c))
PRINTF_SRCS = $(shell find stdio/ft_printf/src -name "*.c" 2>/dev/null)
GNL_SRCS = $(wildcard stdio/gnl/*.c)
ALL_SRCS = $(SRCS) $(PRINTF_SRCS) $(GNL_SRCS)
# Exclude every main.c from the library to avoid multiple definition
ALL_SRCS := $(filter-out %/main.c,$(ALL_SRCS))

# Object files with directory structure preserved
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(ALL_SRCS))

# Header files
HEADERS = $(wildcard *.h)

# Find all unique directories containing .h files in libft, always include root dir
HEADER_DIRS := $(shell find . -type f -name '*.h' -exec dirname {} \; | sort -u)
HEADER_DIRS += .
INCLUDE_FLAGS := $(foreach dir,$(HEADER_DIRS),-I$(dir))

# Add INCLUDE_FLAGS to CFLAGS
CFLAGS += $(INCLUDE_FLAGS) -g3

# Progress/animation settings
PROGRESS_WIDTH ?= 30
COUNTER_FILE := $(OBJ_DIR)/.build_count
SPIN_FILE := $(OBJ_DIR)/.spin_state
TOTAL_OBJS := $(words $(OBJS))

# Default rule: build the library
ifeq ($(MLX_ENABLED),1)
all: $(MINILIBX_LIB) $(NAME)
else
all: $(NAME)
endif

# Build MiniLibX only if present; otherwise skip gracefully
$(MINILIBX_LIB):
	@echo "$(BRIGHT_CYAN)🔧 Building MiniLibX...$(RESET)"
	@if [ -d "$(MINILIBX_DIR)" ] && { [ -f "$(MINILIBX_DIR)/Makefile" ] || [ -f "$(MINILIBX_DIR)/makefile" ]; }; then \
		$(MAKE) -C $(MINILIBX_DIR) $(MLX_FLAGS) || true; \
		if [ ! -f "$(MINILIBX_LIB)" ] && [ -f "$(MLX_ALT_LIB)" ]; then \
			cp "$(MLX_ALT_LIB)" "$(MINILIBX_LIB)"; \
			echo "$(YELLOW)[MiniLibX] Fallback: copied mlx.a -> libmlx.a$(RESET)"; \
		fi; \
	else \
		echo "$(YELLOW)[MiniLibX] Skipping (not present)$(RESET)"; \
	fi

# Prepare progress state before building objects
.PHONY: progress_init
progress_init:
	@mkdir -p $(OBJ_DIR)
	@rm -f $(COUNTER_FILE) $(SPIN_FILE)
	@echo 0 > $(COUNTER_FILE)
	@echo 0 > $(SPIN_FILE)
	@printf "$(BRIGHT_MAGENTA)🚀 Starting build of $(NAME) ($(TOTAL_OBJS) objects)$(RESET)\n"

# Rule to build the library
$(NAME): progress_init $(OBJS)
	@{ \
		# Finalize progress to 100% (visual polish) \
		count=$$( [ -f "$(COUNTER_FILE)" ] && cat "$(COUNTER_FILE)" || echo 0 ); \
		total=$(TOTAL_OBJS); \
		width=$(PROGRESS_WIDTH); \
		percent=100; \
		done_chars=$$width; \
		bar_done=$$(printf "%0.s#" $$(seq 1 $$done_chars)); \
		# Show a final full bar line before archiving \
		printf "\r$(BRIGHT_CYAN)[✔]$(RESET) $(DIM)building$(RESET) $(YELLOW)%-30s$(RESET) $(BRIGHT_GREEN)[%s] %3d%%$(RESET) (%d/%d)\n" \
			"finalizing" "$$bar_done" "$$percent" "$$total" "$$total"; \
	}
	@printf "$(BRIGHT_MAGENTA)📦 Archiving library...$(RESET)\n"
	@$(AR) $(NAME) $(OBJS)
	@printf "$(BRIGHT_GREEN)✓ $(NAME) created successfully!$(RESET)\n"

# Object compilation rule with live spinner and inline progress bar
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@{ \
		# Start a spinner while compiling this file \
		i=0; \
		spinner() { \
			i=0; \
			while :; do \
				case $$((i % 4)) in \
					0) sym='|';; 1) sym='/';; 2) sym='-';; 3) sym='\\';; \
				esac; \
				printf "\r$(BRIGHT_CYAN)[%s]$(RESET) $(DIM)compiling$(RESET) $(YELLOW)%-30s$(RESET)" "$$sym" "$(notdir $<)"; \
				i=$$((i + 1)); \
				sleep 0.1; \
			done; \
		}; \
		spinner & SPIN_PID=$$!; \
		# Compile \
		$(CC) $(CFLAGS) -c $< -o $@; STATUS=$$?; \
		# Stop spinner \
		kill -9 $$SPIN_PID >/dev/null 2>&1 || true; \
		wait $$SPIN_PID 2>/dev/null || true; \
		# Progress accounting \
		count=0; [ -f "$(COUNTER_FILE)" ] && count=$$(cat "$(COUNTER_FILE)"); \
		count=$$((count + 1)); echo $$count > "$(COUNTER_FILE)"; \
		total=$(TOTAL_OBJS); \
		[ $$total -eq 0 ] && total=1; \
		percent=$$((100 * count / total)); \
		# Clamp percent to [0..100] visually \
		if [ $$percent -gt 100 ]; then percent=100; fi; \
		if [ $$percent -lt 0 ]; then percent=0; fi; \
		width=$(PROGRESS_WIDTH); \
		done_chars=$$((percent * width / 100)); \
		[ $$done_chars -gt $$width ] && done_chars=$$width; \
		bar_done=$$(printf "%0.s#" $$(seq 1 $$done_chars)); \
		bar_pad=$$(printf "%0.s " $$(seq 1 $$((width - done_chars)))); \
		if [ $$STATUS -eq 0 ]; then \
			printf "\r$(BRIGHT_CYAN)[✔]$(RESET) $(DIM)building$(RESET) $(YELLOW)%-30s$(RESET) $(BRIGHT_GREEN)[%s%s] %3d%%$(RESET) (%d/%d)" \
				"$(notdir $<)" "$$bar_done" "$$bar_pad" "$$percent" "$$count" "$$total"; \
		else \
			printf "\r$(BRIGHT_RED)[✗]$(RESET) $(YELLOW)%-30s$(RESET) $(BRIGHT_RED)FAILED$(RESET)\n" "$(notdir $<)"; \
			exit $$STATUS; \
		fi; \
	}

build :
	@call(build_lib($(MINILIBX), all));
	
# Enhanced clean with visual feedback
clean:
	@echo "$(BRIGHT_RED)🧹 Cleaning object files...$(RESET)"
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(YELLOW)Removing $(OBJ_DIR)/ directory...$(RESET)"; \
		$(RM) -r $(OBJ_DIR); \
		echo "$(GREEN)✅ Object files cleaned$(RESET)"; \
	else \
		echo "$(DIM)No object files to clean$(RESET)"; \
	fi
	@rm -f $(COUNTER_FILE) $(SPIN_FILE)
	@echo "$(BRIGHT_RED)🧹 Cleaning MiniLibX...$(RESET)"
	@if [ -d "$(MINILIBX_DIR)" ] && { [ -f "$(MINILIBX_DIR)/Makefile" ] || [ -f "$(MINILIBX_DIR)/makefile" ]; }; then \
		$(MAKE) -C $(MINILIBX_DIR) clean || true; \
	else \
		echo "$(DIM)Skipping MiniLibX clean (not present)$(RESET)"; \
	fi

# Enhanced fclean with visual feedback
fclean: clean
	@echo "$(BRIGHT_RED)🔥 Deep cleaning...$(RESET)"
	@if [ -f "$(NAME)" ]; then \
		echo "$(YELLOW)Removing library $(NAME)...$(RESET)"; \
		$(RM) $(NAME); \
		echo "$(GREEN)✅ Library removed$(RESET)"; \
	else \
		echo "$(DIM)No library to remove$(RESET)"; \
	fi
	@echo "$(BRIGHT_RED)🔥 Deep cleaning MiniLibX...$(RESET)"
	@if [ -d "$(MINILIBX_DIR)" ] && { [ -f "$(MINILIBX_DIR)/Makefile" ] || [ -f "$(MINILIBX_DIR)/makefile" ]; }; then \
		$(MAKE) -C $(MINILIBX_DIR) clean || true; \
	else \
		echo "$(DIM)Skipping MiniLibX deep clean (not present)$(RESET)"; \
	fi

# Rebuild
re: fclean all

# Debug mode with enhanced feedback
debug: CFLAGS += -g3 -fsanitize=address
debug: 
	@echo "$(BRIGHT_YELLOW)🐛 DEBUG MODE ENABLED$(RESET)"
	@echo "$(YELLOW)Flags: $(CFLAGS)$(RESET)"
	@$(MAKE) re --no-print-directory
	@echo "$(BRIGHT_YELLOW)🔍 Debug build completed with AddressSanitizer$(RESET)"

# Build a test executable from a main.c in a subdirectory
# Usage: make test TEST=window
TEST ?=

ifeq ($(TEST),)
TEST_MAIN :=
else
TEST_MAIN := $(shell find . -type f -path "*/$(TEST)/main.c" | head -n 1)
endif

TEST_EXE := $(TEST)

.PHONY: test $(TEST_EXE)
mode_42:
	@$(trans_remove_c)
mode_lab:
	@$(trans_add_c)

test: $(TEST_EXE)

norminette:
	find . -path "./minilibx-linux" -prune -o -name "*.c" -exec norminette {} +

# Optional link flags for tests (only when MiniLibX is available)
ifeq ($(MLX_ENABLED),1)
LINK_MLX := $(MINILIBX_LIB) -lX11 -lXext -lm
else
LINK_MLX :=
endif

$(TEST_EXE): $(MINILIBX_LIB) $(NAME)
ifneq ($(strip $(TEST_MAIN)),)
	$(CC) $(CFLAGS) -o $@ $(TEST_MAIN) $(NAME) $(LINK_MLX)
else
	@echo "No main.c found for test '$(TEST)'"
	@exit 1
endif