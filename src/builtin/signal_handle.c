#include "built.h"

void ctrl_c(int sign)
{
	(void)sign;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
