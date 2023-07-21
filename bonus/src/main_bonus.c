/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:23 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/17 22:10:48 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	process_loop(int *infile, char *envp[], t_pipe **p_data);
t_pipe	*init_prog(int *infile, int *outfile, char *argv[], int argc);
void	run_last_process(t_pipe **p_data, int *outfile, char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	int		n_cmds;
	t_pipe	*p_data;
	int		infile;
	int		outfile;
	int		i;

	if (argc < 5)
		error();
	p_data = init_prog(&infile, &outfile, argv, argc);
	i = -1;
	n_cmds = argc - 3;
	while (n_cmds-- != 1)
	{
		p_data->cmd = argv[2 + ++i];
		process_loop(&infile, envp, &p_data);
	}
	p_data->cmd2 = argv[2 + ++i];
	run_last_process(&p_data, &outfile, envp);
	n_cmds = argc - 3;
	while (n_cmds-- != 0)
		wait(NULL);
	free(p_data);
	return (0);
}

t_pipe	*init_prog(int *infile, int *outfile, char *argv[], int argc)
{
	t_pipe	*tmp;

	tmp = malloc(sizeof(t_pipe));
	if (tmp == NULL)
		error();
	*infile = open(argv[1], O_RDONLY, 0644);
	if (*infile < 0)
		error();
	*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		error();
	return (tmp);
}

void	process_loop(int *infile, char *envp[], t_pipe **p_data)
{
	if (pipe((*p_data)->pip) < 0)
		error();
	(*p_data)->pid = fork();
	if ((*p_data)->pid < 0)
		error();
	if ((*p_data)->pid == 0)
		run_child(*p_data, *infile, envp);
	close((*p_data)->pip[1]);
	close(*infile);
	*infile = (*p_data)->pip[0];
}

void	run_last_process(t_pipe **p_data, int *outfile, char *envp[])
{
	(*p_data)->pid2 = fork();
	if ((*p_data)->pid2 < 0)
		error();
	if ((*p_data)->pid2 == 0)
		run_child2(*p_data, *outfile, envp);
	close((*p_data)->pip[0]);
	close((*p_data)->pip[1]);
	close(*outfile);
}
