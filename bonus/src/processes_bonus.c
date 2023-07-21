/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/21 21:28:05 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

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

void	run_child(t_pipe *data, int infile, char *envp[])
{
	close(data->pip[0]);
	duplicate_fd(infile, STDIN_FILENO);
	duplicate_fd(data->pip[1], STDOUT_FILENO);
	exec_process(data->cmd, envp);
}

void	run_child2(t_pipe *data, int outfile, char *envp[])
{
	duplicate_fd(data->pip[0], STDIN_FILENO);
	duplicate_fd(outfile, STDOUT_FILENO);
	exec_process(data->cmd2, envp);
}
