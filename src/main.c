/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:23 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/11 15:37:15 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// int	main(int argc, char *argv[], char *envp[])
// {
// 	int		pip[2];
// 	pid_t	pid;
// 	pid_t	pid2;

// 	if (argc == 5)
// 	{
// 		if (pipe(pip) < 0)
// 			error();
// 		pid = fork();
// 		if (pid < 0)
// 			error();
// 		if (pid == 0)
// 			run_child(argv, envp, pip);
// 		pid2 = fork();
// 		if (pid2 < 0)
// 			error();
// 		if (pid2 == 0)
// 			run_child2(argv, envp, pip);
// 		close(pip[0]);
// 		close(pip[1]);
// 		waitpid(pid, NULL, 0);
// 		waitpid(pid2, NULL, 0);
// 	}
// 	return (0);
// }

int	main(int argc, char *argv[], char *envp[])
{
	int		n_cmds;
	t_pipe	*p_data;
	int		infile;
	int		outfile;
	int		i;

	infile = open(argv[1], O_RDONLY, 0644);
	if (infile < 0)
		error();
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error();
	p_data = malloc(sizeof(t_pipe));
	if (p_data == NULL)
		error();
	i = -1;
	n_cmds = argc - 4;
	while (n_cmds != 0)
	{
		p_data->cmd = argv[2 + ++i];
		if (pipe(p_data->pip) < 0)
			error();

		p_data->pid = fork();
		if (p_data->pid < 0)
			error();
		if (p_data->pid == 0)
			run_child(p_data, infile, envp);

		p_data->cmd2 = argv[2 + ++i];
		close(p_data->pip[1]);
		p_data->pid2 = fork();
		if (p_data->pid2 < 0)
			error();
		if (p_data->pid2 == 0)
			run_child2(p_data, outfile, envp);

		close(p_data->pip[0]);
		n_cmds--;
		if (n_cmds != 0)
			dup2(outfile, infile);
	}
	n_cmds = argc - 4;
	while (n_cmds != 0)
	{
		wait(NULL);
		n_cmds--;
	}
	free(p_data);
	return (0);
}
