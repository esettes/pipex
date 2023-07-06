#include <pipex.h>

#define SIZE 16
char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";
  
int main(int argc, char *argv[])
{
	char buff[SIZE];
	int p[2], i, bytes;
	pid_t	pid;

	// pid = fork();

	if (pipe(p) < 0)
		error();

	if ((pid = fork()) == 0)
	{
		close(p[1]);
		printf("Child pid: %i\n", pid);
		while ((bytes = read(p[0], buff, SIZE)) > 0)
			write(1, buff, bytes);
		close(p[0]);
	}
	else
	{
		close(p[0]);
		ft_strlcpy(buff, msg1, SIZE);
		write(p[1], buff, ft_strlen(buff));
		close(p[1]);
		printf("Parent pid: %i\n", pid);
	}
	error();
	waitpid(pid, NULL, 0);
	//dup2(p[0], 0);
	return 0;
}
