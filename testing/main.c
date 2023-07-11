# include "libft.h"
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "sys/types.h"
# include "fcntl.h"
# include "sys/wait.h"
# include "errno.h"
# include "string.h"

/* funcion que recoge dos argumentos y el argumento dos se ejecute sobre el 
 argumento uno en sistema utilizando la libreria stdlib y sin usar
 mi historial ni mi cache*/

int main(int argc, char *argv[], char *envp[])
