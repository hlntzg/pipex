/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/20 17:56:47 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function check the existence and accessibility for reading the infile. */
void	access_infile(char *file)
{
	if (access(file, F_OK | R_OK) == -1) 
 	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);  // ENOENT or EACCES
		//return (EXIT_FAILURE); exit the program?
	}
}

void	wait_children_processes(t_pipex *data, pid_t *pid, int *status)
{
	int	i;

	i = 0;
	while (i < data->cmds)
		waitpid(pid[i++], status, 0);
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}
	
void	child_process(t_pipex *data, int process)
{
	if (i == 0)
	{
		data->infile = open_file(); // work on this function, open and handle error
		// Duplicate file descriptors instead of calling dup_fd
		if (dup2(data->infile, STDIN) == -1)
			show_error(data, NULL, DUP2, FAILSTD);
		if (dup2(data->fd[1], STDOUT) == -1)
			show_error(data, NULL, DUP2, FAILSTD);
		// Close the file descriptors
		close(data->infile);
		close(data->fd[1]);
	}
	else
	{
		data->outfile = open_file();
		// Duplicate file descriptors instead of calling dup_fd
		if (dup2(data->fd[0], STDIN) == -1)
			show_error(data, NULL, DUP2, FAILSTD);
		if (dup2(data->outfile, STDOUT) == -1)
			show_error(data, NULL, DUP2, FAILSTD);
		// Close the file descriptors
		close(data->fd[0]);
		close(data->outfile);
	}
	close_fd(data);
	execute_cmd(); // work on this function
	exit(0); // work on this function 
}

int	pipex(t_pipex *data)
{
	pid_t	pid[data->cmds];
	int	i;
	int	status;

	i = 0;
	while (i < data->cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			ft_putstr_fd("fork failed", STDERR);
			ft_putstr_fd(":\t", STDERR);
			ft_putstr_fd(strerror(errno), STDERR); 
			exit(EXIT_FAILURE); // exit the program? 
		}
		if (pid[i] == 0)
			child_process(data, i);
		i++;
	}
	close_fd(data);
	wait_children_processes(data, pid, &status);
	return (get_exit_code(status));
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
