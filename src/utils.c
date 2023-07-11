/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:39 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/11 14:08:40 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	exec_process(char *cmd, char *envp[])
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd, ' ');
	path = get_path(cmds[0], envp);
	if (!path)
	{
		free_split(cmds);
		error();
	}
	if (execve(path, cmds, envp) < 0)
		error();
}

void	error(void)
{
	ft_putstrc_fd(RED_, strerror(errno), 2);
	exit(EXIT_FAILURE);
}

void	duplicate_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
		error();
}
