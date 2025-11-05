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


/*
	Lexical layer.
	The enum classifies the kinds of tokens possible
		that the lexer can find.
*/
typedef enum e_token_type
{
    T_WORD,					//normal word like "ls"
    T_PIPE,					// | 
    T_REDIR_IN,				// <
    T_REDIR_OUT,			// >
    T_REDIR_APPEND,			// >>
    T_HEREDOC,				// <<
} t_token_type;

/*
	Store each token in a linked list node.
*/

typedef struct s_token
{
    char            *word;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef struct  s_shell
{
    char    **args;
	char	**env;
	int		exit_status;
} t_shell;

typedef struct s_tokenizer
{
	int					redir_in;
	int					redir_out;
	int					redir_append;
	int					heredoc;
	int					heredoc_fd;
	char				**limits;
	char				**args;
	char				**input;
	char				**output;
	struct s_tokenizer	*next;
} t_tokenizer;


//
extern  t_shell *global_sh;

//Prototypes
void    init_shell(t_shell *shell, char	**env);
char	**cpy_env(char **env);
void	set_signals(void);
void	sighandler(int signal);
void    main_loop(t_shell *shell, char **env);


#endif
