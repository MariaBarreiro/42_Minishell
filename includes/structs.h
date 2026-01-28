#ifndef STRUCTS_H
# define STRUCTS_H

	typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
} t_token_type;

typedef struct s_token
{
	char            *value;
	int				quoted;
	t_token_type    type;
	struct s_token  *next;
} t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

typedef	struct s_output
{
	char			*file;
	int				append;
	struct s_output	*next;
} t_output;

typedef struct s_fd_backup
{
	int				stdin_fd;
	int				stdout_fd;
} t_fd_backup;

typedef struct s_cmd_block
{
	int					redir_in;
	int					heredoc;
	char				**limits;
	char				**args;
	char				**input;
	int					n_outputs;
	t_output			*outputs;
	struct s_cmd_block	*next;
} t_cmd_block;

typedef struct s_mini
{
	int					exit_stts;
	t_env				*my_env;
	t_cmd_block			*cmd;
} t_mini;

#endif
