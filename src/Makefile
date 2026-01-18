NAME = minitest

SRC = builtin/cd.c builtin/echo.c builtin/pwd.c builtin/env.c builtin/exit.c builtin/export.c builtin/unset.c\
	builtin/signal_handle.c builtin/env_utils.c builtin/export_utils.c\
	builtin/utils.c\
	execution/exec_builtin.c execution/execution.c execution/exec_utils.c execution/exec_multiple.c\
	execution/setup_redirections.c execution/exec_errors.c execution/execute_cmd.c\
	main_test.c init_env.c

OBJS = $(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra 
GFLAGS = -g3 -fsanitize=address

%.o: %.c
	@cc -c $(FLAGS) -g -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo COMPILED

clean:
	@rm -f $(OBJS)
	@echo OBJS removeds

fclean: clean 
	@rm $(NAME)
	@echo EXECUTABLE removed

re: fclean all

.PHONY: bonus all clean fclean re
