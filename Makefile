NAME = pipex

SRCS = cmd_check.c error.c pipex.c proccess.c transaction.c
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@make re -C ./libft
	@$(CC) ${OBJS} -Llibft -lft -o ${NAME}
	@echo "\033[33m ____  __  ____  ____  _  _"
	@echo "(  _ \(  )(  _ \(  __)( \/ )"
	@echo " ) __/ )(  ) __/ ) _)  )  ("
	@echo "(__)  (__)(__)  (____)(_/\_)\033[0m"

clean:
	make fclean -C ./libft
	rm -rf $(OBJS)


fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	@echo "\n\033[31mDeleting EVERYTHING!\n"

re: fclean all


.PHONY: all clean fclean re
