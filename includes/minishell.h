#ifndef	MINISHELL_H
# define	MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termios.h>
# include <curses.h>
# include "../libs/42_Libft/42_Gnl/get_next_line.h"			
# include "../libs/42_Libft/Inc/libft.h"

void	main_loop(void);

#endif
