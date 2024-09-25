/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/25 16:53:09 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* */
static void	wait_children_processes(pid_t *pid, int *status)
{
	int	i;

	i = 0;
	while (i < 2)
		waitpid(pid[i++], status, 0);
}

/* */
static int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

/* This function open the specific file, duplicate the file descriptors and 
 * close them before calling the execute_cmds(). */
static void	child_process(t_pipex *data, int process)
{
	if (process == 0)
	{
		open_file(data, process);
		if (dup2(data->infile, STDIN) == -1)
			perror("\ndup2 infile"); // ERROR
		if (dup2(data->fd[1], STDOUT) == -1)
			perror("\ndup2 pipe write"); // ERROR
		close(data->infile);
		close(data->fd[1]);
	}
	else
	{
		open_file(data, process);
		if (dup2(data->fd[0], STDIN) == -1)
			perror("\ndup2 pipe read"); // ERROR
		if (dup2(data->outfile, STDOUT) == -1)
			perror("\ndup2 outfile"); // ERROR
		close(data->fd[0]);
		close(data->outfile);
	}
	close_fd(data);
	go_to_process(data, data->av[process + 2]);
	if (data->infile > -1)
		close(data->infile);
	if (data->outfile > -1)
		close(data->outfile);
	close_fd(data);
	exit(EXIT_SUCCESS);
}

/* */
int	pipex(t_pipex *data)
{
	pid_t	pid[2];
	int	i;
	int	status;

	i = 0;
	while (i < 2)
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
	wait_children_processes(pid, &status);
	return (get_exit_code(status));
}
