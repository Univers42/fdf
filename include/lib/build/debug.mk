# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    debug.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 19:30:00 by dlesieur          #+#    #+#              #
#    Updated: 2025/05/27 19:10:29 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════
# ║                            DEBUG TARGETS                                ║
# ════════════════════════════════════════════════════════════════════════════

include $(BUILD_DIR)/common.mk

# Debug flags
DEBUG_FLAGS = -g3 -DDEBUG
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
OPTIMIZE_FLAGS = -O0

# Debug build
.PHONY: debug
debug: CFLAGS += $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS)
debug: fclean all
	$(call print_status,$(YELLOW),DEBUG,Debug mode enabled)

# Debug with sanitizers
.PHONY: debug_sanitize
debug_sanitize: CFLAGS += $(DEBUG_FLAGS) $(SANITIZE_FLAGS) $(OPTIMIZE_FLAGS)
debug_sanitize: fclean all
	$(call print_status,$(YELLOW),DEBUG,Debug mode with sanitizers enabled)

# Release build
.PHONY: release
release: CFLAGS += -O3 -DNDEBUG
release: fclean all
	$(call print_status,$(GREEN),RELEASE,Release mode enabled)

# Profile build
.PHONY: profile
profile: CFLAGS += -pg -O2
profile: fclean all
	$(call print_status,$(BLUE),PROFILE,Profile mode enabled)

# Static analysis
.PHONY: analyze
analyze:
	$(call print_status,$(CYAN),ANALYZE,Running static analysis...)
	@cppcheck --enable=all --std=c99 $(SRC_DIRS) 2>/dev/null || true
	@scan-build make fclean all 2>/dev/null || true
