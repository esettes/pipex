#include "pipex.h"

void	run_child(char *argv[], char *envp[], int *pip)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile < 0)
		error();
	close(pip[0]);
	duplicate_fd(infile, STDIN_FILENO);
	duplicate_fd(pip[1], STDOUT_FILENO);
	exec_process(argv[2], envp);
}

void	run_parent(char *argv[], char *envp[], int *pip)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error();
	close(pip[1]);
	duplicate_fd(pip[0], STDIN_FILENO);
	duplicate_fd(outfile, STDOUT_FILENO);
	exec_process(argv[3], envp);
}
