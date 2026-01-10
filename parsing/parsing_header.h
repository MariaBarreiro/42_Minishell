#ifndef	PARSING_HEADER_H
# define	PARSING_HEADER_H

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
# include <signal.h>
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
	int				quoted;
    t_token_type    type;
    struct s_token  *next;
} t_token;

/*
	The shell state. The "session". The "short-term memory".
*/

typedef struct s_env 
{
	char			*name;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

//Revise!!!//
typedef	struct s_output
{
	char	*file;
	int		append;
} t_output;

/*
	Parsed representation. What comes after lexing and parsing.
	Each t_command_block corresponds to one command in the pipeline.
		For example: cat < file | grep hello are 2 command_block linked together.
*/

typedef struct s_cmd_block
{
	int					redir_in;		//Index for '<' that tells how many input redirection have been collected so far.
	int					redir_out;		//Index for '>' that tells how many output redirections have been collected so far.
	int					redir_append;	//Counter for '>>'
	int					heredoc;		//Index for '<<' that tells how many heredoc redirections have been collected so far.
	int					heredoc_fd;		//Fd for the temporary heredoc file.
	char				**limits;		//Delimiter words for heredocs (ex: EOF).
	char				**args;			//The command and its arguments.
	char				**input;		//Filenames for '<' redirections.
	char				**output;		//Filenames for '>' and '>>' redirections.
	int					n_outputs;
	t_output			*outputs;		
	struct s_cmd_block	*next;		//Pointer to the next command in the pipeline.
} t_cmd_block;


//"Shell state" struct.//
typedef struct s_mini
{
	int					exit_stts;
	char				*input;
	t_token				*token;
	t_env				*env;
	t_cmd_block			*cmd;
} t_mini;


//Prototypes

//Main//
void			init_minishell(t_mini *mini, char **envp);
void			main_loop(t_mini *mini);
//Signals//
void	set_signals(void);
void	sighandler(int signal);
//Main utils//
int				check_interactive(void);
int				check_delimiter(char c);
int				check_spaces(char *str);

//Tokens//

//Tokenizer//
t_cmd_block		*tokenizer(t_mini *mini, char *line);
t_token			*tokenization(t_mini *mini, char *line);

//Init token//
t_token			*init_token(t_mini *mini, t_token *head, char *line, int *i);
char			*get_tokens(t_mini *mini, const char *line, int *i);
char			*get_single_token(t_mini *mini, const char *line, int *i);

//New Token//
void			new_token(t_token **new_node, t_token **head, t_token **current);

//Token Utils//
t_token_type	get_type(char *value);
int				is_exact_token(const char *token, const char *value);
// int				redir_out_check(const char *token, const char *value, long len);
// int				redir_append_check(const char *token, const char *value, long len);
// int				redir_in_check(const char *token, const char *value, long len);
// int				pipe_check(const char *token, const char *value, long len);
// int				heredoc_check(const char *token, const char *value, long len);

//Env variables//
char			*var_expansion(t_mini *mini, char *fragment, char quote_type);
char			*get_variable(t_env *env, char *fragment, int exit_status);
char			*get_brace(t_env *env, char *fragment, char *start);
char			*get_env_value(t_env *env, char *var_name);

//Env Utils//
char			*concat(char *start, char *fragment, char *var_exit_value, int i);

//Blocks//
t_cmd_block		*parse_blocks(t_token *token, t_mini *mini);
t_cmd_block		*new_block(int ac);
int				fill_block(t_cmd_block *block, t_token **token, t_mini *mini, t_cmd_block *head);

//Block Utils//
int				count_ac(t_token *temp_token);

//Handle Redirections//
int				handle_redir(t_cmd_block *block, t_token **token, int type);
int				handle_heredoc(t_cmd_block *block, t_token **token);

//Error//
void			error(t_token *token, char *message, int exit_code);
int				redir_error(t_cmd_block *head, t_cmd_block *block, t_mini *mini, t_token *token);
// static int		pipe_error(t_cmd_block *head, t_mini *mini);

//Free//
void			free_tokens(t_token *token);
void			free_blocks(t_cmd_block *head);
void			free_arrays(char **array);



#endif
