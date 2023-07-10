#include <pipex.h>

int main(int argc, char *argv[], char *envp[])
{
	int		pip[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(pip) < 0)
			error();
		pid = fork();
		if (pid < 0)
			error();
		if (pid == 0)
		{
			run_child(argv, envp, pip);
		}
		waitpid(pid, NULL, 0);
		run_parent(argv, envp, pip);
	}
	return 0;
}
