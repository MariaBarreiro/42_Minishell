NAME = built
SRC = main_test.c echo.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc -Wall -Werror -Wextra $(OBJS) -o $(NAME)
clean: rm $(OBJS)

fclean: clean rm $(NAME)

re: fclean all