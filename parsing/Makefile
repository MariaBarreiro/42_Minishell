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

LIB_PATH							= ../libs/42_Libft/
LIB_NAME							= libft.a
LIB										= $(LIB_PATH)$(LIB_NAME)

INC_PATH							= headers/

SRC_PATH							= .

SRC_FILES							= env_variables.c

MAIN_SRC_PATH					= main/

MAIN_SRC_FILES							= bool_utils.c
MAIN_SRC_FILES							+= main_loop.c
MAIN_SRC_FILES							+= parsing_main.c
MAIN_SRC_FILES							+= signals.c

TOKEN_SRC_PATH				= tokens/

TOKEN_SRC_FILES							= tokenizer.c
TOKEN_SRC_FILES							+= init_tokens.c
TOKEN_SRC_FILES							+= new_token.c
TOKEN_SRC_FILES							+= utils_type_check.c

BLOCKS_SRC_PATH				= blocks/

BLOCKS_SRC_FILES						= blocks.c
BLOCKS_SRC_FILES						+= blocks_utils.c
BLOCKS_SRC_FILES						+= handle_redirs.c



SRC								= $(addprefix $(SRC_PATH), $(SRC_FILES))
SRC								+= $(addprefix $(MAIN_SRC_PATH), $(MAIN_SRC_FILES))
SRC								+= $(addprefix $(TOKEN_SRC_PATH), $(TOKEN_SRC_FILES))
SRC								+= $(addprefix $(BLOCKS_SRC_PATH), $(BLOCKS_SRC_FILES))


OBJS_DIR						= obj
OBJS							= $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                   Compiler                                   #
# **************************************************************************** #

CC								= cc
CFLAGS         		= -Wall -Wextra -Werror -g
INC     	        = -I$(INC_PATH)
INC						    += -I$(LIB_PATH)/42_Gnl/ 
INC								+= -I$(LIB_PATH)

# **************************************************************************** #
#                                   Commands                                   #
# **************************************************************************** #

RM              = rm -rf
MKDIR						= mkdir -p

# **************************************************************************** #
#                                    Rules                                     #
# **************************************************************************** #
 
all: $(LIB) $(NAME)

$(LIB): 
	@$(MAKE) -C $(LIB_PATH)

$(OBJS_DIR):
	@$(MKDIR) obj
	@echo "Objects directory created!"

$(OBJS_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
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
