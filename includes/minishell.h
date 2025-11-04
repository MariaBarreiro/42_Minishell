#ifndef	MINISHELL_H
# define	MINISHELL_H

//Includes
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

//Defines


//Structs

typedef enum e_token_type
{
    T_WORD,
    T_PIPE,
    T_REDIR_IN, 
    T_REDIR_OUT,
    T_REDIR_APPEND,
    T_REDIR_FILE,
    T_HEREDOC,
//    T_HEREDOC_DELIMITER,
} t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *word;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

typedef struct  s_shell
{
    char    *input;
    t_token *tokens;
} t_shell;


//
extern  t_shell *global_sh;

//Prototypes
void    main_loop(void);
void    init_shell(t_shell *shell);
#endif
