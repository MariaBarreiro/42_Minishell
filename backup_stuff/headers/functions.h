#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

/*------------MAIN-----------------------------*/
t_shell			*init_shell(t_sell *shell, char **env);
char			**cpy_env(char **env);
void			set_signals(void);
void			sighandler(int signal);

/*------------Main Loop------------------------*/
void			main_loop(t_shell *shell, char **env);
bool			check_interactive(void);


/*------------TOKENS---------------------------*/
t_cmd_block		*tokenizer(t_shell *shell, char *line);
t_token			*tokenization(t_shell *shell, char *line);

/*------------Init Tokens----------------------*/
t_token			*init_token(t_shell *shell, t_token *head, char *line, int *i);
char			*get_tokens(t_shell *shell, const char *line, int *i);
char			*get_single_token(t_shell *shell, const char *line, int *i);

/*------------Variables Expansion--------------*/
char			*variable_expansion(t_shell *shell, char *fragment, char quote_type);
char			*get_variable(char **env, char *fragment, int exit_status);
char			*concat(char *start, char *fragment, char *var_exit_value, int i);
char			*get_brace(char **env, char *fragment, char *start);
char			*get_env_value(char **env, char *var_name);

/*------------New Token------------------------*/
void			new_token(t_token **new_token, t_token **head, t_token **current);
t_token_type	get_type(char *value);

/*------------Utils Type-----------------------*/
bool			redir_out_token_check(const char *token, const char *value, size_t len_value);
bool			redir_append_token_check(const char *token, const char *value, size_t len_value);
bool			redir_in_token_check(const char *token, const char *value, size_t len_value);
bool			pipe_token_check(const char *token, const char *value, size_t len_value);
bool			heredoc_token_check(const char *token, const char *value, size_t len_value);

/*------------BLOCKS---------------------------*/
t_cmd_block		*parse_blocks(t_token *token, t_shell *shell);


/*------------Utils General---------------------*/
bool			check_delimiter(char c);
bool			check_spaces(char *str);
#endif
