NAME = pipex
SRCS = error.c pipex.c procces.c ft_split.c  pipex_utils.c

OBJECTS = $(SRCS:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror
AR = ar -rc

all: $(NAME)

$(NAME) : $(OBJECTS)
	@ar -rc $@ $?
	$(CC) $(CFLAGS) pipex.c $(NAME) -o pipex

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf	$(NAME)
re: fclean all

.PHONY : all bonus clean fclean re
