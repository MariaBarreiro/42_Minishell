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
	corresponding to the specified names, which shall cause them to be
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

int all_variables()
{
	printf("under construction, be paciente!!!\n");
	return (0);
}


equal ()
{

}

int ft_export(char **args, t_env **env)
{
	
	if (!args[1])
		return (all_variables());
	
	if (equal())
	{

	}
	else
	{

	}
	//printf("under construction, be paciente!!!\n");
	return (0);
}