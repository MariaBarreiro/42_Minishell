/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:29:51 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:29:51 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//Main//
int				main(int ac, char **av, char **envp);
void			init_minishell(t_mini *mini, char **envp);
void			main_loop(t_mini *mini);
char			*read_input_line(void);

//Signals//
void			set_signals(void);
void			sighandler(int signal);

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
void			set_token_value(t_mini *mini, t_token *new, char *line, int *i);
char			*get_tokens(t_mini *mini, const char *line,
					int *i, int *quoted, int expand);
char			*get_single_token(t_mini *mini,
					const char *line, int *i, int *quoted, int expand);

//New Token//
void			new_token(t_token **new_node,
					t_token **head, t_token **current);

//Token Utils//
t_token_type	get_type(char *value);
int				is_exact_token(const char *token,
					const char *value, long len);
int				is_double_redirect(const char *line, int *i);
char			*extract_quoted_fragment(const char *line,
					int *i, char *quote_type);
char			*extract_unquoted_fragment(const char *line, int *i);
int				is_heredoc_limiter(const char *line, int i);

//Env variables//
char			*var_expansion(t_mini *mini, char *fragment, char quote_type);
char			*get_variable(t_env *env, char *fragment, int exit_status);
char			*get_brace(t_env *env, char *fragment, char *start);
char			*env_value(t_env *env, char *var_name);

//Env List//
t_env			*build_env_node(const char *entry);
t_env			*add_new_node(char *key, char *value);
void			list_add_back(t_env **env, t_env *new_node);
t_env			*init_env(char **envp);

//Env Utils//
char			*concat(char *start, char *fragment,
					char *var_exit_value, int i);

//Blocks//
t_cmd_block		*parse_blocks(t_token *token, t_mini *mini);
t_cmd_block		*new_block(int ac);
int				fill_block(t_cmd_block *block, t_token **token,
					t_mini *mini, t_cmd_block *head);

//Block Utils//
int				count_ac(t_token *temp_token);

//Handle Redirections//
int				handle_redir(t_cmd_block *block, t_token **token, int type);
int				add_input_redir(t_cmd_block *block, t_token *token);
int				add_output_redir(t_cmd_block *block, t_token *token,
					int append);
int				handle_heredoc(t_cmd_block *block, t_token **token);
int				handle_pipe_token(t_token **token, t_cmd_block *head,
					t_mini *mini);

//Error//
void			error(t_token *token, char *message, int exit_code);
int				redir_error(t_cmd_block *head, t_cmd_block *block,
					t_mini *mini, t_token *token);
int				pipe_error(t_cmd_block *head, t_mini *mini);

//Free//
void			free_tokens(t_token *token);
void			free_blocks(t_cmd_block *head);
void			free_arrays(char **array);
void			free_output_list(t_output *output);
void			free_block_arrays(t_cmd_block *block);

//Execution//

int				execute_pipeline(t_mini *mini);
int				is_builtin(char **arg);
int				exec_builtin(char **arg, t_mini *mini);

//Execute Mutiple//
int				execute_multiple(t_mini *mini);
int				apply_redirections(t_cmd_block *cmd);
int				handle_heredocs(t_cmd_block *cmd);
int				execute_cmd(t_cmd_block *cmd, t_env *envp);
void			free_array(char **str);
void			print_error(char *cmd, char *error);

//Execute Utils//
t_pipe			*create_pipes(int n);
void			wait_all_children(pid_t *pids, int n, t_mini *mini);
void			close_all_pipes(t_pipe *pipes, int n_cmds);
int				count_cmds(t_cmd_block *cmd);
void			restore_fds(t_fd_backup *b);
void			save_fds(t_fd_backup *b);
int				validate_cmd(char *cmd, char *path);

//Built-in Commands//

int				ft_echo(char **arg);
int				ft_cd(t_env **my_env, char **arg);
int				ft_pwd(char **cmd, t_env *env);
int				ft_export(t_env **my_env, char **args);
int				ft_unset(t_env **my_env, char **args);
int				ft_env(t_env *my_env, char **arg);
int				ft_exit(char **args, int exit_stts);

//Env Utils//
char			*get_env_value(char *key, t_env *my_env);
int				init_minimal_env(t_env **env);
void			update_env(char *key, char *value, t_env **my_env, int create);
t_env			*new_node(char *key, char *valuev);
void			lst_add_back(t_env **my_env, t_env *new_node);
int				print_variables(t_env *my_env);
int				env_key_exists(char *key, t_env *my_env);
char			*get_key(char *args);
int				ft_strcmp(const char *s1, const char *s2);
void			env_add_back(t_env **lst, t_env *new);
char			*ft_itoa(int n);
int				ft_atoll(const char *nptr);
int				ft_strsearch(char *str, char c);
void			append_env(char *key, char *value, t_env **env);

#endif
