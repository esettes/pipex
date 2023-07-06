#include "pipex.h"

void error(void)
{
	ft_putstrc_fd(RED_, strerror(errno), 2);
	exit(EXIT_FAILURE);
}