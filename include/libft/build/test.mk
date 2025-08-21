# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 19:30:00 by dlesieur          #+#    #+#              #
#    Updated: 2025/05/27 19:10:29 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════
# ║                             TEST TARGETS                                ║
# ════════════════════════════════════════════════════════════════════════════

include $(BUILD_DIR)/common.mk

# Test program configuration
TEST_PROGRAM = test_program
TEST_SOURCES = main.c
TEST_FLAGS = -L. -l$(basename $(NAME))

# Main test target
.PHONY: test
test: $(NAME) $(TEST_SOURCES)
	$(call print_status,$(CYAN),TEST,Compiling test program...)
	@$(CC) $(CFLAGS) $(TEST_SOURCES) $(TEST_FLAGS) -o $(TEST_PROGRAM)
	$(call print_status,$(GREEN),TEST,Running test program:)
	@./$(TEST_PROGRAM)

# Unit test target
.PHONY: unit_test
unit_test: $(NAME)
	$(call print_status,$(BLUE),UNIT_TEST,Running unit tests...)
	@for test in tests/*.c; do \
		if [ -f "$$test" ]; then \
			$(CC) $(CFLAGS) "$$test" $(TEST_FLAGS) -o test_runner; \
			./test_runner; \
			$(RM) test_runner; \
		fi; \
	done

# Memory test with valgrind
.PHONY: valgrind
valgrind: $(NAME) $(TEST_SOURCES)
	$(call print_status,$(YELLOW),VALGRIND,Running memory checks...)
	@$(CC) $(CFLAGS) -g3 $(TEST_SOURCES) $(TEST_FLAGS) -o $(TEST_PROGRAM)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_PROGRAM)

# Performance test
.PHONY: benchmark
benchmark: $(NAME) $(TEST_SOURCES)
	$(call print_status,$(MAGENTA),BENCHMARK,Running performance tests...)
	@$(CC) $(CFLAGS) -O3 $(TEST_SOURCES) $(TEST_FLAGS) -o $(TEST_PROGRAM)
	@time ./$(TEST_PROGRAM)

# Clean test artifacts
.PHONY: clean_test
clean_test:
	$(call print_status,$(RED),CLEAN,Removing test artifacts...)
	@$(RM) $(TEST_PROGRAM) test_runner
