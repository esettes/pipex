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
		duplicate_fd(infile, STDIN_FILENO);
		duplicate_fd(p[1], STDOUT_FILENO);
		close(p[0]);
		exec_process(argv[2], envp);
	}
	waitpid(pid, NULL, 0);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error();
	duplicate_fd(p[0], STDIN_FILENO);
	duplicate_fd(outfile, STDOUT_FILENO);
	close(p[1]);
	exec_process(argv[3], envp);
	return 0;
}

