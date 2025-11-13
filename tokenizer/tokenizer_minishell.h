#ifndef	TOKENIZER_MINISHELL_H
# define	TOKENIZER_MINISHELL_H

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
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

/*
	The shell state. The "session". The "short-term memory".
*/

typedef struct  s_shell
{
	char    **args;						//Temporary storage when executing a command.
	char	**env;						//Current environment variables.
	char	**export_variables;			//List of variables marked for export.
	int		exit_status;				//Last command exit status ($?).
	char	**history;					//Command history.
} t_shell;

/*
	Parsed representation. What comes after lexing and parsing.
	Each t_command_block corresponds to one command in the pipeline.
		For example: cat < file | grep hello are 2 command_block linked together.
*/

typedef struct s_command_block
{
	int					redir_in;		//Counter or fd for '<'
	int					redir_out;		//Counter or fd for '>'
	int					redir_append;	//Counter for '>>'
	int					heredoc;		//Counter for '<<'
	int					heredoc_fd;		//Fd for the temporary heredoc file.
	char				**limits;		//Delimiter words for heredocs (ex: EOF).
	char				**args;			//The command and its arguments.
	char				**input;		//Filenames for '<' redirections.
	char				**output;		//Filenames for '>' and '>>' redirections.
	struct s_command_block	*next;		//Pointer to the next command in the pipeline.
} t_command_block;

//
extern  t_shell *global_sh;

//Prototypes
t_shell			*init_shell(t_shell *shell, char	**env);
char			**cpy_env(char **env);
void			set_signals(void);
void			sighandler(int signal);
void			main_loop(t_shell *shell, char **env);
t_command_block	*tokenizer(t_shell *shell, char *line);
bool			check_spaces(char *str);
t_token			*tokenization(t_shell *shell, char *line);
t_token			*init_token(t_shell *shell, t_token *head, char *line, int *i);
void			new_token(t_token **new, t_token **head, t_token **current);
void			free_tokens(t_token *token);
void			error(t_token *token, char *message, int code);
bool			check_delimiter(char c);
char			*get_tokens(t_shell *shell, const char *line, int *i);
char			*get_single_token(t_shell *shell, const char *line, int *i);
char			*variable_expansion(t_shell *shell, char *fragment, char quote_type);
char			*get_variable(char **env, char *fragment, int exit_status);
char			*concat(char *start, char *fragment, char *var_exit_value, int i);
t_token_type	get_type(char *value);
bool			redir_out_token_check(const char *token, const char *value, size_t len_value);
bool			redir_append_token_check(const char *token, const char *value, size_t len_value);
bool			redir_in_token_check(const char *token, const char *value, size_t len_value);
bool			pipe_token_check(const char *token, const char *value, size_t len_value);
bool			heredoc_token_check(const char *token, const char *value, size_t len_value);
t_command_block	*parse_blocks(t_token *token, t_shell *shell);
int				count_ac(t_token *temp_token);
t_command_block	*new_block(int ac);
bool			fill_block(t_command_block *block,t_token **token, t_shell *shell, t_command_block *head);
bool			handle_redirect(t_command_block *block, t_token **token, int type);
static int		pipe_error(t_command_block *head, t_shell *shell);




#endif
