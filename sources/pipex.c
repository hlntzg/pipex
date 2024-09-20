/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/20 12:18:11 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function check the existence and accessibility for reading the infile. */
void	access_infile(char *file)
{
	if (access(file, F_OK | R_OK) == -1) 
 	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(":\t", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);  // ENOENT or EACCES
		//return (EXIT_FAILURE); exit the program?
	}
}

int	pipex(t_pipex *data)
{
	pid_t	pid[2];
	int	i;

	i = 0;
	while (i < data->cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			ft_putstr_fd("fork failed", STDERR);
			ft_putstr_fd(":\t", STDERR);
			ft_putstr_fd(strerror(errno), STDERR); 
			// exit the program? 
		}
		if (pid[i] == 0)
		//	child_process(data, i);
		{
			printf("child process %d\n", i);
			close_fd(data);
			exit(0);
		}
		i++;
	}
	close_fd(data);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	printf("parent process\n");
	return (0);
}

void	close_fd(t_pipex *data)
{
	if (data->fd[0] > -1)
		close(data->fd[0]);
	if (data->fd[1] > -1)
		close(data->fd[1]);
	free(data->fd);
	data->fd = NULL;
}
