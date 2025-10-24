# **************************************************************************** #
#                                    Config                                    #
# **************************************************************************** #
MAKE = make 
SHELL = bash
# **************************************************************************** #
#                                    NAMES                                     #
# **************************************************************************** #
NAME = libft.a
# **************************************************************************** #
#                                    Paths                                     #
# **************************************************************************** #
INC_PATH        = ./Inc/

SRC_PATH        = ./Src/

SRC_FILES           = ft_bzero.c
SRC_FILES           += ft_isalnum.c
SRC_FILES           += ft_isalpha.c 
SRC_FILES           += ft_isascii.c
SRC_FILES						+= ft_isdigit.c 
SRC_FILES						+= ft_isprint.c
SRC_FILES						+= ft_memcpy.c
SRC_FILES						+= ft_memmove.c
SRC_FILES						+= ft_memset.c
SRC_FILES						+= ft_strchr.c
SRC_FILES						+= ft_strlen.c
SRC_FILES						+= ft_strrchr.c
SRC_FILES						+= ft_tolower.c
SRC_FILES						+= ft_toupper.c
SRC_FILES						+= ft_memchr.c
SRC_FILES						+= ft_strncmp.c 
SRC_FILES						+= ft_memcmp.c
SRC_FILES						+= ft_strnstr.c
SRC_FILES						+= ft_strlcat.c
SRC_FILES						+= ft_strlcpy.c
SRC_FILES						+= ft_atoi.c
SRC_FILES						+= ft_calloc.c
SRC_FILES						+= ft_strdup.c
SRC_FILES						+= ft_substr.c
SRC_FILES						+= ft_strjoin.c
SRC_FILES						+= ft_strtrim.c
SRC_FILES						+= ft_split.c
SRC_FILES						+= ft_itoa.c
SRC_FILES						+= ft_strmapi.c
SRC_FILES						+= ft_striteri.c
SRC_FILES						+= ft_putchar_fd.c
SRC_FILES						+= ft_putstr_fd.c
SRC_FILES						+= ft_putendl_fd.c
SRC_FILES						+= ft_putnbr_fd.c

GNL_PATH						= ./42_Gnl/

GNL_FILES						+= get_next_line.c
GNL_FILES						+= get_next_line_bonus.c
GNL_FILES						+= get_next_line_utils.c
GNL_FILES						+= get_next_line_utils_bonus.c

PRINTF_PATH					= ./42_Ft_Printf/
PRINTF_NAME					= libftprintf.a
PRINTF							= $(PRINTF_PATH)$(PRINTF_NAME)

PRINTF_FILES						+= 42_Ft_Printf/ft_printf.c
PRINTF_FILES						+= 42_Ft_Printf/ft_printf_hex.c
PRINTF_FILES						+= 42_Ft_Printf/ft_printf_ptr.c
PRINTF_FILES						+= 42_Ft_Printf/ft_printf_str.c
PRINTF_FILES						+= 42_Ft_Printf/ft_printf_uns.c
PRINTF_FILES						+= 42_Ft_Printf/ft_utils.c
PRINTF_FILES						+= 42_Ft_Printf/ft_utils2.c


SRC									= $(addprefix $(SRC_PATH), $(SRC_FILES))
SRC									+= $(addprefix $(GNL_PATH), $(GNL_FILES))

OBJS_DIR						= Obj
OBJS								= $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                   Compiler                                   #
# **************************************************************************** #

CC              = cc
CFLAGS          = -Wall -Wextra -Werror
INC             = -I $(INC_PATH) 
INC							+= -I $(INC_PATH)/42_Gnl 
INC							+= -I $(PRINTF_PATH)

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
	@echo "📌 Libft Compiled!"

clean:
	@$(MAKE) clean -C $(PRINTF_PATH)
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(PRINTF_PATH)
	@$(RM) $(NAME) $(OBJS_DIR)
    
re: fclean all
