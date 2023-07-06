#include <pipex.h>

int main(int argc, char *argv[], char *envp[])
{
	int		p[2];
	pid_t	pid;
	int		infile;
	int		outfile;

	if (pipe(p) < 0)
		error();
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
			error();
		close(p[0]);
		// execute
	}
	waitpid(pid, NULL, 0);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error();
	close(p[1]);
	// execute
	return 0;
}
