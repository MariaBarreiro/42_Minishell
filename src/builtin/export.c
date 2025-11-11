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
*/
int	ft_export(void)
{
	printf("under construction, be paciente!!!\n");
	return (0);
}