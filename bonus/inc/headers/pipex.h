/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:09:44 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/11 17:27:30 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "sys/types.h"
# include "fcntl.h"
# include "sys/wait.h"
# include "errno.h"
# include "string.h"

typedef struct s_pipe
{
	int		pip[2];
	pid_t	pid;
	pid_t	pid2;
	char	*cmd;
	char	*cmd2;
}	t_pipe;

# define COLORED 1

# if COLORED
#  define RED_    "\x1b[31m"
#  define GREEN_  "\x1b[32m"
#  define YELLOW_ "\x1b[33m"
#  define BLUE_   "\x1b[34m"
#  define VIOLET_ "\x1b[35m"
#  define CYAN_   "\x1b[36m"
#  define RESET_  "\x1b[0m"
# else
#  define RED_    ""
#  define GREEN_  ""
#  define YELLOW_ ""
#  define BLUE_   ""
#  define VIOLET_ ""
#  define CYAN_   ""
#  define RESET_  ""
# endif

void	error(void);
/**
 * @brief Redirects the file descriptor oldfd to newfd.
 * 
 * @param oldfd
 * @param newfd
 */
void	duplicate_fd(int oldfd, int newfd);
void	exec_process(char *cmd, char *envp[]);
void	run_child(t_pipe *data, int infile, char *envp[]);
void	run_child2(t_pipe *data, int outfile, char *envp[]);

#endif
