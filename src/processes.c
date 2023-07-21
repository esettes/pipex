/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/21 21:20:28 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exec_process(char *cmd, char *envp[])
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd, ' ');
	if (cmd_have_current_path(cmds[0]))
	{
		free_split(cmds);
		ft_putstrc_fd(RED_, "No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	if (cmd_have_path(cmds[0]))
	{
		path = ft_strdup(cmds[0]);
		if (execve(path, cmds, envp) < 0)
			error();
		return ;
	}
	path = get_path(cmds[0], envp);
	if (!path)
	{
		free_split(cmds);
		ft_putstrc_fd(RED_, "No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmds, envp) < 0)
		error();
}

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

void	run_child2(char *argv[], char *envp[], int *pip)
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
