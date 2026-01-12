#ifndef STRUCTS_H
#define STRUCTS_H

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


typedef struct  s_shell
{
	char    **args;						//Temporary storage when executing a command.
	char	**env;						//Current environment variables.
	char	**export_variables;			//List of variables marked for export.
	int		exit_status;				//Last command exit status ($?).
} t_shell;
*/
/*
	Parsed representation. What comes after lexing and parsing.
	Each t_cmd_block corresponds to one command in the pipeline.
		For example: cat < file | grep hello are 2 cmd_block linked together.
*/

typedef struct s_cmd_block
{
	int					redir_in;		//Index for '<' that tells how many input redirection have been collected so far.
	int					redir_out;		//Index for '>' that tells how many output redirections have been collected so far.
	int					redir_append;	//Counter for '>>'
	int					heredoc;		//Index for '<<' that tells how many heredoc redirections have been collected so far.
	char				**limits;		//Delimiter words for heredocs (ex: EOF).
	char				**args;			//The command and its arguments.
	char				**input;		//Filenames for '<' redirections.
	char				**output;		//Filenames for '>' and '>>' redirections.
	struct s_cmd_block	*next;		//Pointer to the next command in the pipeline.
} t_cmd_block;

//
extern  t_shell *global_sh;

#endif
