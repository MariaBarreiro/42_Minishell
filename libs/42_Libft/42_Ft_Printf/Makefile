# **************************************************************************** #
#                                    Config                                    #
# **************************************************************************** #
MAKE = make
SHELL = bash
# **************************************************************************** #
#                                    NAMES                                     #
# **************************************************************************** #
NAME = libftprintf.a
EXEC = a.out
# **************************************************************************** #
#                                    Paths                                     #
# **************************************************************************** #
INC_PATH        = ./Inc/

SRC_PATH        = ./Src/

SRC_FILES       = ft_printf.c
SRC_FILES				+= ft_utils.c
SRC_FILES				+= ft_utils2.c
SRC_FILES				+= ft_printf_ptr.c
SRC_FILES				+= ft_printf_hex.c
SRC_FILES				+= ft_printf_str.c
SRC_FILES				+= ft_printf_uns.c

SRC             = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJS_DIR				= Obj
OBJS				   	= $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                   Compiler                                   #
# **************************************************************************** #
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g
INC             = -I $(INC_PATH)
# **************************************************************************** #
#                                   Commands                                   #
# **************************************************************************** #
RM              = rm -rf
AR              = ar rcs
MKDIR           = mkdir -p
# **************************************************************************** #
#                                    Rules                                     #
# **************************************************************************** #
 
all: $(NAME)

$(OBJS_DIR):
	@mkdir -p Obj

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS_DIR) $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "📚 Ft_Printf Compiled!"


clean:
	$(RM) $(OBJS)

fclean: clean
	 $(RM) $(NAME) $(OBJS_DIR)
    
re: fclean all
