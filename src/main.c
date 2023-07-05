#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MSGSIZE 16
char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";
  
int main(int argc, char *argv[])
{
	char inbuf[MSGSIZE];
	int p[2], i;
	int pid;

	pid = fork();

	if (pipe(p) < 0)
		exit(1);
 
	/* continued */
	/* write pipe */
	
	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);

	if (pid == 0)
	{
		printf("Child pid: %i\n", pid);
	}
	else
	{
		printf("Parent pid: %i\n", pid);
	}
	for (i = 0; i < 3; i++) {
		/* read pipe */
		read(p[0], inbuf, MSGSIZE);
		printf("%s\n", inbuf);
	}

	dup2(p[0], 0);
	return 0;
}

/*
void	ft_putendl_fd(char *color, char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*color)
		write(fd, color++, 1);
	while (*s)
		write (fd, s++, 1);
	color = "\x1b[0m";
	write (fd, "\n", 1);
}
*/
