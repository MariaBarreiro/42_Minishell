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

SRC_FILES						= main.c

SRC								= $(addprefix $(SRC_PATH), $(SRC_FILES))

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
