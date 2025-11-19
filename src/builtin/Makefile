NAME = built
SRC = cd.c echo.c pwd.c env.c exit.c export.c unset.c\
	signal_handle.c env_utils.c\
	main_test.c builtin_command.c utils.c init_envp.c
OBJS = $(SRC:.c=.o)
FLAGS += -Wall -Werror -Wextra
GFLAGS = -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJS)

fclean: clean 
	@rm $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re