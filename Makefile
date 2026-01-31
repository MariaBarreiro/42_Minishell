# **************************************************************************** #
#                                    Config                                    #
# **************************************************************************** #

MAKE = make 
SHELL = bash

# **************************************************************************** #
#                                    Names                                     #
# **************************************************************************** #

NAME = minishell

# **************************************************************************** #
#                                    Paths                                     #
# **************************************************************************** #

LIB_PATH						= ./libs/42_Libft/
LIB_NAME						= libft.a
LIB								= $(LIB_PATH)$(LIB_NAME)

INC_PATH						= ./includes/

SRC_PATH						= ./src/

SRC_FILES				  		= main.c
SRC_FILES							+= env_variables.c
SRC_FILES							+= utils_free.c
SRC_FILES							+= utils_error.c
SRC_FILES							+= utils_booleans.c
SRC_FILES							+= env_list.c
SRC_FILES							+= init_env.c

MAIN_SRC_PATH					= ./src/parsing/main/

MAIN_SRC_FILES				+= main_loop.c
MAIN_SRC_FILES				+= parsing_main.c
MAIN_SRC_FILES				+= signals.c

TOKEN_SRC_PATH				= ./src/parsing/tokens/

TOKEN_SRC_FILES				= tokenizer.c
TOKEN_SRC_FILES				+= init_tokens.c
TOKEN_SRC_FILES				+= new_token.c

BLOCKS_SRC_PATH				= ./src/parsing/blocks/

BLOCKS_SRC_FILES			= blocks.c
BLOCKS_SRC_FILES			+= blocks_utils.c
BLOCKS_SRC_FILES			+= handle_redirs.c

BUILTIN_SRC_PATH			= ./src/builtin/

BUILTIN_SRC_FILES			= cd.c
BUILTIN_SRC_FILES			+= echo.c
BUILTIN_SRC_FILES			+= env.c
BUILTIN_SRC_FILES			+= env_utils.c
BUILTIN_SRC_FILES			+= exit.c
BUILTIN_SRC_FILES			+= export.c
BUILTIN_SRC_FILES			+= export_utils.c
BUILTIN_SRC_FILES			+= pwd.c
BUILTIN_SRC_FILES			+= unset.c
BUILTIN_SRC_FILES			+= utils_builtin.c

EXECUTION_SRC_PATH		= ./src/execution/

EXECUTION_SRC_FILES		= exec_builtin.c
EXECUTION_SRC_FILES		+= exec_errors.c
EXECUTION_SRC_FILES		+= exec_multiple.c
EXECUTION_SRC_FILES		+= exec_utils.c
EXECUTION_SRC_FILES		+= exec_cmd.c
EXECUTION_SRC_FILES		+= execution.c
EXECUTION_SRC_FILES		+= setup_redirections.c
EXECUTION_SRC_FILES		+= fds_utils.c

SRC								= $(addprefix $(SRC_PATH), $(SRC_FILES))
SRC								+= $(addprefix $(MAIN_SRC_PATH), $(MAIN_SRC_FILES))
SRC								+= $(addprefix $(TOKEN_SRC_PATH), $(TOKEN_SRC_FILES))
SRC								+= $(addprefix $(BLOCKS_SRC_PATH), $(BLOCKS_SRC_FILES))
SRC								+= $(addprefix $(BUILTIN_SRC_PATH), $(BUILTIN_SRC_FILES))								
SRC								+= $(addprefix $(BUILTIN_LST_PATH), $(BUILTIN_LST_FILES))								
SRC								+= $(addprefix $(EXECUTION_SRC_PATH), $(EXECUTION_SRC_FILES))								

OBJS_DIR						= obj
OBJS							= $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                   Compiler                                   #
# **************************************************************************** #

CC							= cc
CFLAGS          			= -Wall -Wextra -Werror -g
INC     			        = -I$(INC_PATH)
INC						    += -I$(LIB_PATH)/42_Gnl/ 
INC							+= -I$(LIB_PATH)

# **************************************************************************** #
#                                   Commands                                   #
# **************************************************************************** #

RM              = rm -rf

# **************************************************************************** #
#                                    Rules                                     #
# **************************************************************************** #
 
all: $(LIB) $(NAME)

$(LIB): 
	@$(MAKE) -C $(LIB_PATH)

$(OBJS_DIR):
	@mkdir -p obj
	@echo "Objects directory created!"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIB) -o $(NAME) -lreadline
	@echo "Compilation completed!"

clean:
	@$(MAKE) clean -C $(LIB_PATH)
	@$(RM) $(OBJS)
	@echo "Objects removed successfully!"

fclean: clean
	@$(MAKE) fclean -C $(LIB_PATH)
	@$(RM) $(NAME) $(OBJS_DIR)
	@echo "Program removed successfully!"

re: fclean all
		@echo "Re-compile was successfull!"

PHONY: bonus all clean fclean re
