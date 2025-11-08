NAME = built
SRC = main_test.c cd.c echo.c pwd.c \
	builtin_command.c utils.c
OBJS = $(SRC:.c=.o)
FLAGS += -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJS)

fclean: clean 
	@rm $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re