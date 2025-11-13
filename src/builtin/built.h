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
int		ft_cd(char **arg, t_env **env);
int		ft_pwd(void);
int		ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
int		ft_env(t_env **venv, char **env);
int		ft_exit(void);

//_____________________signal handle____________________________________
void	ctrl_c(int sign);

//_____________________"fake_main"____________________________________

int		main(int ac, char **av, char **envp);
void	main_loop(t_env **envp);

//____________________delete later ____________________________________

int		builtin_command(char **venv, char *arg);
int		find_token(char **arg);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_env	*init_env(char **venv);

#endif