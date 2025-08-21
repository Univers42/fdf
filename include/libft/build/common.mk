# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    common.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 19:30:00 by dlesieur          #+#    #+#              #
#    Updated: 2025/07/30 01:12:30 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════
# ║                           COMMON VARIABLES                               ║
# ════════════════════════════════════════════════════════════════════════════

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L. -lft -pthread -lm
AR = ar rcs
RM = rm -f

# Directories
OBJ_DIR = obj
BUILD_DIR = build

# Colors and formatting
include $(BUILD_DIR)/colors.mk

# ════════════════════════════════════════════════════════════════════════════
# ║                           COMMON FUNCTIONS                               ║
# ════════════════════════════════════════════════════════════════════════════

# Function to create directory structure
define create_dirs
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BUILD_DIR)
endef

# Function to print status messages
define print_status
	@printf "$(1)$(BOLD)[$(2)] $(3)$(RESET)\n"
endef

# Function to clean object files
define clean_objects
	$(call print_status,$(RED),CLEAN,Removing object files...)
	@$(RM) -r $(OBJ_DIR)
endef

# Function to clean library
define clean_library
	$(call print_status,$(RED),CLEAN,Removing library $(NAME)...)
	@$(RM) $(NAME)
endef
