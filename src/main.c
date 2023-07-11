#include <pipex.h>

int main(int argc, char *argv[], char *envp[])
{
	int		pip[2];
	int	infile;
	pid_t	pid;
	pid_t	pid2;
	int	outfile;

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

		pid2 = fork();
		
		if (pid2 < 0)
			error();
		if (pid2 == 0)
		{
			
			run_parent(argv, envp, pip);
		}
		close(pip[0]);
		close(pip[1]);
		waitpid(pid, NULL, 0);
		
		waitpid(pid2, NULL, 0);
	}
	return 0;
}
