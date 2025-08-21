# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    library.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 19:30:00 by dlesieur          #+#    #+#              #
#    Updated: 2025/05/27 19:10:29 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════
# ║                           LIBRARY BUILD RULES                           ║
# ════════════════════════════════════════════════════════════════════════════

# Include common definitions
include $(BUILD_DIR)/common.mk

# Progress counter
COUNTER = 0

# Pre-build setup
.PHONY: pre_build
pre_build:
	$(call print_status,$(CYAN),BUILD,Building $(NAME)...)
	$(call create_dirs)

# Main library rule
$(NAME): pre_build $(OBJS)
	$(call print_status,$(MAGENTA),ARCHIVE,Creating $(NAME)...)
	@$(AR) $(NAME) $(OBJS)
	$(call print_status,$(GREEN),DONE,Library $(NAME) successfully created!)

# Object compilation rule
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(call print_progress)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Default target
.PHONY: all
all: $(NAME)

# Clean rules
.PHONY: clean
clean:
	$(call clean_objects)

.PHONY: fclean
fclean: clean
	$(call clean_library)

.PHONY: re
re: fclean all
