#ifndef	TOKENIZER_MINISHELL_H
# define	TOKENIZER_MINISHELL_H

//Includes
# include <stdio.h>
# include <fcntl.h>
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
# include <signal.h>
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

typedef struct s_env {
	char			*name;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

/*
	Parsed representation. What comes after lexing and parsing.
	Each t_command_block corresponds to one command in the pipeline.
		For example: cat < file | grep hello are 2 command_block linked together.
*/
typedef	struct s_output
{
	char			*file;
	int				append;
	struct s_output	*next;
} t_output;

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

typedef struct s_mini
{
	int					exit_stts;
	t_cmd_block			*cmd;
	t_env				*my_env;
} t_mini;

//

//Prototypes
/* t_shell			*init_shell(t_shell *shell, char	**env);
char			**cpy_env(char **env);
void			set_signals(void);
void			sighandler(int signal);
void			main_loop(t_shell *shell, char **env);
t_command_block	*tokenizer(t_shell *shell, char *line);
bool			check_spaces(char *str);
t_token			*tokenization(t_shell *shell, char *line);
t_token			*init_token(t_shell *shell, t_token *head, char *line, int *i);
void			new_token(t_token **new_token, t_token **head, t_token **current);
void			free_tokens(t_token *token);
void			error(t_token *token, char *message, int code);
bool			check_delimiter(char c);
char			*get_tokens(t_shell *shell, const char *line, int *i);
char			*get_single_token(t_shell *shell, const char *line, int *i);
char			*variable_expansion(t_shell *shell, char *fragment, char quote_type);
char			*get_variable(char **env, char *fragment, int exit_status);
char			*concat(char *start, char *fragment, char *var_exit_value, int i);
char			*get_brace(char **env, char *fragment, char *start);
char			*get_env_value(char **env, char *var_name);
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
bool			handle_redir(t_command_block *block, t_token **token, int type);
bool			redir_error(t_command_block *head, t_command_block *block, t_shell *shell, t_token *token);
void			free_arrays(char	**array);
bool			handle_heredoc(t_command_block *block, t_token **token);
static int		pipe_error(t_command_block *head, t_shell *shell);
void			free_blocks(t_command_block *head); */


/* -------------------------------execute------------------------------------------------------- */
int		execute_pipeline(t_mini *mini);
int		is_builtin(char **arg);
int		exec_builtin(char **arg, t_mini *mini);

//void	apply_redirections(t_command_block *cmd);
/* -------------------------------execute mutiple-------------------------------------------------- */
int		execute_multiple(t_cmd_block **list);
void	child_process(t_cmd_block *cmd, int (*p)[2], int i, int n);
void	setup_child_pipes(int i, int total, int (*p)[2]);
void	setup_redirections(t_cmd_block *cmd); ///////////// (HERE_DOC)
int		execute_cmd(t_cmd_block *cmd, t_env *envp); ////////////
int		execute_builtin_child( t_cmd_block *cmd); ////////////////

//----------------------execute utils------------------------------------------
int		(*create_pipes(int n))[2];
void	wait_all_children(pid_t *pids, int n);
void	close_all_pipes(int	*pipes, int n); ////////////
int		count_cmds(t_cmd_block *cmd);


//______________________built-in commands_____________________________

int		ft_echo(char **arg);
int		ft_cd(t_env **my_env, char **arg);
int		ft_pwd(void); //t_env *my_env, char **cmd
int		ft_export(t_env **my_env, char **args);
int		ft_unset(t_env **my_env, char **args);
int		ft_env(t_env *my_env, char **arg);
int		ft_exit(char **args, int exit_stts);

//______________________env utils_____________________________
char	*get_env_value(char *key, t_env *my_env);
void	update_env(char *key, char *value, t_env **my_env, int create);
t_env	*new_node(char *key, char *valuev);
void	lst_add_back(t_env **my_env, t_env *new_node);
int		print_variables(t_env *my_env);
int		env_key_exists(char *key, t_env *my_env);
char	*get_key(char *args);
int		ft_strcmp(const char *s1, const char *s2); //<<<< add to libft
int		ft_lstsize(t_env *lst); //<<<< add to libft

//_____________________signal handle____________________________________
void	ctrl_c(int sign);

//_____________________"fake_main"____________________________________

int		main(int ac, char **av, char **envp);
void	main_loop(t_env **envp);
int		builtin_type(char **arg);

//____________________delete later ____________________________________

int		builtin_command(t_env **my_env, char *arg);
int		find_token(char **arg);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substr_split(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
void	env_add_back(t_env **lst, t_env *new);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
t_env	*init_env(char **envp);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_atoll(const char *nptr);
int	ft_strsearch(char *str, char c); //<< add to libft


#endif