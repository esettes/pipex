/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:23 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/11 17:32:54 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char *argv[], char *envp[])
{
	int		pip[2];
	pid_t	pid;
	pid_t	pid2;

	if (argc == 5)
	{
		if (pipe(pip) < 0)
			error();
		pid = fork();
		if (pid < 0)
			error();
		if (pid == 0)
			run_child(argv, envp, pip);
		pid2 = fork();
		if (pid2 < 0)
			error();
		if (pid2 == 0)
			run_child2(argv, envp, pip);
		close(pip[0]);
		close(pip[1]);
		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}
