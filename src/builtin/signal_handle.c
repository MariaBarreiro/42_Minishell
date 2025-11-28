#include "built.h"

void	ctrl_c(int sign)
{
	char buffer[1024];
	printf("%s", getcwd(buffer, sizeof(buffer)));//3(C), 4(D) e 28(\);
}