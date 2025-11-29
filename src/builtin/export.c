#include "built.h"

/*
Without any arguments, the command will generate or display all exported variables. Below is an example of the expected output.
> export
declare -x COLORTERM="truecolor"
declare -x DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/102755/bus"
declare -x DESKTOP_SESSION="ubuntu"
declare -x DISPLAY=":0"
declare -x DOCKER_HOST="unix:///run/user/102755/docker.sock"
declare -x FT_HOOK_NAME="login-user"

export — set the export attribute for variables

The shell shall give the export attribute to the variables
	corresponding to the specified names, w01hich shall cause them to be
	in the environment of subsequently executed commands. If the name
	of a variable is followed by =word, then the value of that
	variable shall be set to word.

EXAMPLES:
Export PWD and HOME variables:

	export PWD HOME

	Set and export the PATH variable:

	export PATH=/local/bin:$PATH

export should start with a latter

ex: 
export 123aaa
export: `123aaa': not a valid identifier

export =
export: `=': not a valid identifier

only print vars if is_exported == (1) TRUE;

Retorno:

0 → sucesso
1 → erro (ex: variável inválida, sintaxe errada)

struct: {name, value, exported, next *}

| Caso                | Exemplo            | Ação                                   | Retorno |
| ------------------- | ------------------ | -------------------------------------- | ------- |
| Sem argumentos      | `export`           | Imprime todas exportadas               | 0       |
| Com `VAR=value`     | `export VAR=value` | Cria/atualiza e marca como exportada   | 0       |
| Com `VAR` (sem `=`) | `export VAR`       | Marca como exportada (se existir)      | 0       |
| Nome inválido       | `export 1VAR=abc`  | Mostra erro `"not a valid identifier"` | 1       |

*/

int	valid_identifier(char *s)
{
	int i = 0;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return 0;
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return 0;
		i++;
	}
	return 1;
}

static int	error_identifier(char *arg)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(" : not a valid identifier", 2);
	return (1);
}

static int	ft_strsearch(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char *get_key(char *venv)
{
	int	equal;

	equal = ft_strsearch(venv, '=');
	if (equal == -1)
		return (ft_strdup(venv));
	return (ft_substr(venv, 0, equal));
	}

static char *get_value(char *venv)
{
	size_t	len;
	int	equal;

	equal = ft_strsearch(venv, '=');
	len = ft_strlen(venv);
	if (equal == -1 || equal == (int)len - 1)
		return (NULL);
	return (ft_substr(venv, equal + 1, len - (equal + 1)));
}

int	ft_export(t_env **my_env, char **args)
{
	int		i;
	char	*key;
	int		rt;

	rt = 0;
	if (!args[1])
		return (print_variables(*my_env));
	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
			rt = error_identifier(args[i]);
		else
		{
			key = get_key(args[i]);
			if (!env_key_exists(key, *my_env))
				update_env(key, get_value(args[i]), my_env, 1);
			else
				update_env(key, get_value(args[i]), my_env, 0);
		}
		i++;
	}
	return (rt);
}
