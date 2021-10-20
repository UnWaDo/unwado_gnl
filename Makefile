GNL_DIR = ../gnl/
GNL_SOURCES_NAMES = get_next_line.c get_next_line_utils.c
GNL_HEADERS_NAMES = get_next_line.h
BONUSES = get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.h
HEADERS = $(addprefix $(GNL_DIR), $(GNL_HEADERS_NAMES))
SOURCES = $(SOURCES_NAMES) $(addprefix $(GNL_DIR), $(GNL_SOURCES_NAMES))
OBJECTS = $(SOURCES:.c=.o)
EXEC = clang
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
ifndef BUFFER_SIZE
	BUFFER_SIZE = 42
endif
BUFFER_FLAG = -D BUFFER_SIZE=$(BUFFER_SIZE)

TESTS = init check_files simple_test stdin_test directory_test bonus_test
SIMPLE_TEST_OBJS = simple_test/main.o
STDIN_TEST_OBJS = stdin_test/main.o
DIR_TEST_OBJS = directory_test/main.o
TESTS_OBJS = $(SIMPLE_TEST_OBJS) $(STDIN_TEST_OBJS) $(DIR_TEST_OBJS)
TESTS_PROGS = simple_test/simple_test stdin_test/stdin_test directory_test/directory_test

.PHONY: all clean fclean re $(TESTS)

all:			$(TESTS)

%.o:			%.c $(HEADERS) Makefile
	@echo Compiling file $<
	@$(EXEC) $(CFLAGS) -o $@ -c $< $(BUFFER_FLAG) -I$(GNL_DIR)

%.h:
	@echo File $@ is absent, make sure you have correct naming

%.c:
	@echo File $@ is absent, make sure you have correct naming
	$(error No C file $@ found)

init:
	rm -f errors.log

check_files:
	@echo --Performing file checking--
	@for file in $(SOURCES) $(HEADERS); do \
		if test -f "$$file"; then \
			echo File $${file##*/} exists; \
		else \
			echo File $${file##*/} is absent; \
		fi \
	done

simple_test: TEST_DIR = simple_test
simple_test:	$(SIMPLE_TEST_OBJS) $(OBJECTS) $(HEADERS) Makefile
	@echo --Performing Simple Test--
	@$(EXEC) $(CFLAGS) $(SIMPLE_TEST_OBJS) $(OBJECTS) -o $(TEST_DIR)/$@
	@cd $(TEST_DIR) && bash $(TEST_DIR).sh

stdin_test: TEST_DIR = stdin_test
stdin_test:	$(STDIN_TEST_OBJS) $(OBJECTS) $(HEADERS) Makefile
	@echo --Compiling Stdin test. You can perform it manually--
	@$(EXEC) $(CFLAGS) $(STDIN_TEST_OBJS) $(OBJECTS) -o $(TEST_DIR)/$@

directory_test: TEST_DIR = directory_test
directory_test:	$(DIR_TEST_OBJS) $(OBJECTS) $(HEADERS) Makefile
	@echo --Performing Directory Test--
	@$(EXEC) $(CFLAGS) $(DIR_TEST_OBJS) $(OBJECTS) -o $(TEST_DIR)/$@
	@./$(TEST_DIR)/$@

clean:
	rm -f $(OBJECTS) $(TESTS_OBJS) $(TESTS_PROGS)

fclean:			clean
	rm -f $(NAME)

re:				fclean all
