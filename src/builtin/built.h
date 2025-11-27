#ifndef BUILT_H
# define BUILT_H

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
# include <signal.h>

typedef struct s_env {
	char			*name;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;


//______________________built-in commands_____________________________

int		ft_echo(char **arg);
int		ft_cd(t_env **my_env, char **arg);
int		ft_pwd(t_env *my_env, char **cmd);
int		ft_export(t_env *my_env, char **args);
int		ft_unset(t_env *my_env);
int		ft_env(t_env *my_env, char **arg);
int		ft_exit(void);

//______________________env utils_____________________________
char	*get_env_value(char *key, t_env *my_env);
void	update_env(char *key, char *value, t_env **my_env, int create);
t_env	*new_node(char *key, char *valuev);
void	lst_add_back(t_env **my_env, t_env *new_node);

//_____________________signal handle____________________________________
void	ctrl_c(int sign);

//_____________________"fake_main"____________________________________

int		main(int ac, char **av, char **envp);
void	main_loop(t_env **envp);

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
t_env	*init_env(char **envp);
int		ft_strcmp(const char *s1, const char *s2); //<<<<

#endif