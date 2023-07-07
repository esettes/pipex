#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "sys/types.h"
# include "fcntl.h"
# include "sys/wait.h"
# include "errno.h"
# include "string.h"

# define PRINT_	1
# define COLORED 1

# if COLORED
#  define RED_    "\x1b[31m"
#  define GREEN_  "\x1b[32m"
#  define YELLOW_ "\x1b[33m"
#  define BLUE_   "\x1b[34m"
#  define VIOLET_ "\x1b[35m"
#  define CYAN_   "\x1b[36m"
#  define RESET_  "\x1b[0m"
# else
#  define RED_    ""
#  define GREEN_  ""
#  define YELLOW_ ""
#  define BLUE_   ""
#  define VIOLET_ ""
#  define CYAN_   ""
#  define RESET_  ""
# endif

void	error(void);
void	duplicate_fd(int oldfd, int newfd);
void	exec_process(char *cmd, char *envp[]);

#endif
