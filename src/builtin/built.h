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

int		main(int ac, char **av, char **envp);
void	main_loop(void);
int		ft_cd(char *arg);
int		ft_echo(char *arg);
int		ft_pwd(void);

//---------------delete later -------------------------
int	builtin_command(char *arg);
int	find_token(char *arg);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif