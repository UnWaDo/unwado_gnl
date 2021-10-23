GNL_DIR = ../gnl/
GNL_SOURCES_NAMES = get_next_line.c get_next_line_utils.c
GNL_HEADERS_NAMES = get_next_line.h
GNL_BONUS_SOURCES_NAMES = get_next_line_bonus.c get_next_line_utils_bonus.c
GNL_BONUS_HEADERS_NAMES = get_next_line_bonus.h
HEADERS = $(addprefix $(GNL_DIR), $(GNL_HEADERS_NAMES))
SOURCES = $(addprefix $(GNL_DIR), $(GNL_SOURCES_NAMES))
OBJECTS = $(SOURCES:.c=.o)

BONUS_HEADERS = $(addprefix $(GNL_DIR), $(GNL_BONUS_HEADERS_NAMES))
BONUS_SOURCES = $(addprefix $(GNL_DIR), $(GNL_BONUS_SOURCES_NAMES))
BONUS_OBJS = $(BONUS_SOURCES:.c=.o)
EXEC = clang
CFLAGS = -Wall -Wextra -Werror
#CFLAGS += -fsanitize=address
ifndef BUFFER_SIZE
	BUFFER_SIZE = 42
endif
BUFFER_FLAG = -D BUFFER_SIZE=$(BUFFER_SIZE)

CLR_HDR = '\033[0;35m'
CLR_NC = '\033[0m'
CLR_STRT = '\033[0;36m'

TESTS = init check_files simple_test stdin_test directory_test \
	per_line_test bonus_test
SIMPLE_TEST_OBJS = simple_test/main.o
STDIN_TEST_OBJS = stdin_test/main.o
DIR_TEST_OBJS = directory_test/main.o
PER_LINE_TEST_OBJS = per_line_test/main.o per_line_test/lines_utils.o
BONUS_TEST_OBJS = bonus_test/main.o bonus_test/lines_utils.o bonus_test/files_utils.o
TESTS_OBJS = $(SIMPLE_TEST_OBJS) $(STDIN_TEST_OBJS) $(DIR_TEST_OBJS) \
	$(PER_LINE_TEST_OBJS) $(BONUS_TEST_OBJS)
TESTS_PROGS = simple_test/simple_test.out stdin_test/stdin_test.out \
	directory_test/directory_test.out per_line_test/per_line_test.out \
	bonus_test/bonus_test.out

Makefile:	;
.PHONY: all clean fclean re $(TESTS)

all:			$(TESTS)

%_bonus.o: 		%_bonus.c $(BONUS_HEADERS)
	@$(EXEC) $(CFLAGS) -o $@ -c $< $(BUFFER_FLAG) -I$(GNL_DIR)

%.o:			%.c $(HEADERS)
	@$(EXEC) $(CFLAGS) -o $@ -c $< $(BUFFER_FLAG) -I$(GNL_DIR)
%.h:
	@echo File $@ is absent, make sure you have correct naming

%.c:
	@echo File $@ is absent, make sure you have correct naming
	$(error No C file $@ found)

init:	TITLE = Performing check for BUFFER_SIZE=$(BUFFER_SIZE)
init:
	@echo $(CLR_STRT)"--$(TITLE)--"$(CLR_NC)
	@rm -f errors.log

check_files:	TITLE = Performing file checking
check_files:
	@echo $(CLR_HDR)"--$(TITLE)--"$(CLR_NC)
	@for file in $(SOURCES) $(HEADERS); do \
		if test -f "$$file"; then \
			echo File $${file##*/} exists; \
		else \
			echo File $${file##*/} is absent; \
		fi \
	done

simple_test: 		TEST_DIR = simple_test
simple_test: 		TITLE = Performing simple test
simple_test: 		TEST_PREPARATION = $(EXEC) $(CFLAGS) \
			$(SIMPLE_TEST_OBJS) $(OBJECTS) -o $(TEST_DIR)/$(TEST_DIR).out
simple_test: 		TEST_PERFORMING = cd $(TEST_DIR) && bash $(TEST_DIR).sh
simple_test: 		$(SIMPLE_TEST_OBJS) $(OBJECTS) $(HEADERS)
	@echo $(CLR_HDR)"--$(TITLE)--"$(CLR_NC)
	@$(TEST_PREPARATION)
	@$(TEST_PERFORMING)

stdin_test:  		TEST_DIR = stdin_test
stdin_test: 		TITLE = Compiling Stdin test. You can perform it manually
stdin_test: 		TEST_PREPARATION = $(EXEC) $(CFLAGS) \
			$(STDIN_TEST_OBJS) $(OBJECTS) -o $(TEST_DIR)/$(TEST_DIR).out
stdin_test: 		TEST_PERFORMING = 
stdin_test:				$(STDIN_TEST_OBJS) $(OBJECTS) $(HEADERS)
	@echo $(CLR_HDR)"--$(TITLE)--"$(CLR_NC)
	@$(TEST_PREPARATION)
	@$(TEST_PERFORMING)

directory_test:		TEST_DIR = directory_test
directory_test: 	TITLE = Performing directory test
directory_test: 	TEST_PREPARATION = $(EXEC) $(CFLAGS) \
			$(DIR_TEST_OBJS) $(OBJECTS) -o $(TEST_DIR)/$(TEST_DIR).out
directory_test: 	TEST_PERFORMING = ./$(TEST_DIR)/$(TEST_DIR).out
directory_test: 	$(DIR_TEST_OBJS) $(OBJECTS) $(HEADERS)
	@echo $(CLR_HDR)"--$(TITLE)--"$(CLR_NC)
	@$(TEST_PREPARATION)
	@$(TEST_PERFORMING)

per_line_test: 		TEST_DIR = per_line_test
per_line_test: 		TITLE = Performing per line test
per_line_test: 		TEST_PREPARATION = $(EXEC) $(CFLAGS) \
			$(PER_LINE_TEST_OBJS) $(OBJECTS) -o $(TEST_DIR)/$(TEST_DIR).out
per_line_test: 		TEST_PERFORMING = cd $(TEST_DIR) && ./$(TEST_DIR).out
per_line_test: 		$(PER_LINE_TEST_OBJS) $(OBJECTS) $(HEADERS)
	@echo $(CLR_HDR)"--$(TITLE)--"$(CLR_NC)
	@$(TEST_PREPARATION)
	@$(TEST_PERFORMING)

bonus_test: 		TEST_DIR = bonus_test
bonus_test: 		TESTS_OBJS = $(BONUS_TEST_OBJS)
bonus_test: 		TITLE = Performing bonus multiple FD test
bonus_test: 		TEST_PREPARATION = $(EXEC) $(CFLAGS) \
			$(TESTS_OBJS) $(BONUS_OBJS) -o $(TEST_DIR)/$(TEST_DIR).out
bonus_test: 		TEST_PERFORMING = cd $(TEST_DIR) && ./$(TEST_DIR).out
bonus_test: 		$(BONUS_TEST_OBJS) $(BONUS_OBJS) $(BONUS_HEADERS)
	@echo $(CLR_HDR)"--$(TITLE)--"$(CLR_NC)
	@$(TEST_PREPARATION)
	@$(TEST_PERFORMING)

clean:
	@echo Cleaning up files
	@rm -f $(OBJECTS) $(TESTS_OBJS) $(TESTS_PROGS) $(BONUS_OBJS)

fclean:			clean

re:				fclean all
