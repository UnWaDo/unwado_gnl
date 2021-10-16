SOURCES = get_next_line.c get_next_line_utils.c main.c
HEADERS = get_next_line.h
NAME = gnl_test
OBJECTS = $(SOURCES:.c=.o)
EXEC = clang
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE = 500
BUFFER_FLAG = -D BUFFER_SIZE=$(BUFFER_SIZE)
.PHONY: all clean fclean re

$(NAME): $(OBJECTS) $(HEADERS) Makefile
	@echo Compiling project
	@$(EXEC) $(CFLAGS) $(OBJECTS) -o $@

all: $(NAME)

%.o: %.c $(HEADERS) Makefile
	@echo Compiling file $<
	@$(EXEC) $(CFLAGS) -o $@ -c $< $(BUFFER_FLAG)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
