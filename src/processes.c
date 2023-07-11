/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/11 15:32:37 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// void	run_child(char *argv[], char *envp[], int *pip)
// {
// 	int	infile;

// 	infile = open(argv[1], O_RDONLY, 0777);
// 	if (infile < 0)
// 		error();
// 	close(pip[0]);
// 	duplicate_fd(infile, STDIN_FILENO);
// 	duplicate_fd(pip[1], STDOUT_FILENO);
// 	exec_process(argv[2], envp);
// }

void	set_process(t_pipe *data, char *argv[], int pos)
{
	data->cmd = argv[pos];
}

void	run_child(t_pipe *data, int infile, char *envp[])
{
	close(data->pip[0]);
	duplicate_fd(infile, STDIN_FILENO);
	duplicate_fd(data->pip[1], STDOUT_FILENO);
	exec_process(data->cmd, envp);
}

void	run_child2(t_pipe *data, int outfile, char *envp[])
{
	//close(data->pip[1]);
	duplicate_fd(data->pip[0], STDIN_FILENO);
	duplicate_fd(outfile, STDOUT_FILENO);
	exec_process(data->cmd2, envp);
}

// void	run_child2(char *argv[], char *envp[], int *pip)
// {
// 	int	outfile;

// 	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (outfile < 0)
// 		error();
// 	close(pip[1]);
// 	duplicate_fd(pip[0], STDIN_FILENO);
// 	duplicate_fd(outfile, STDOUT_FILENO);
// 	exec_process(argv[3], envp);
// }
