/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/02 16:13:12 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* */
static int	wait_processes(pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < 2)
		waitpid(pid[i++], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

/* This function open the specific file, duplicate the file descriptors and 
 * close them before calling the execute_cmds(). */
static void	child_process(t_pipex *data, int process)
{
	if (process == 0)
	{
		open_file(data, process);
		if (dup2(data->infile, STDIN) == -1)
			exit_failure(data, "read infile", DUP2, EXIT_FAILURE);
//		{
//			log_error("read infile", DUP2);
//			release_resources_and_exit(data, EXIT_FAILURE);
//		}
		if (dup2(data->fd[1], STDOUT) == -1)
			exit_failure(data, "pipe write", DUP2, EXIT_FAILURE);
//		{
//			log_error("pipe write", DUP2);
//			release_resources_and_exit(data, EXIT_FAILURE);
//		}
		close(data->infile);
		close(data->fd[1]);
	}
	else
	{
		open_file(data, process);
		if (dup2(data->fd[0], STDIN) == -1)
			exit_failure(data, "pipe read", DUP2, EXIT_FAILURE);
//		{
//			log_error("pipe read", DUP2);
//			release_resources_and_exit(data, EXIT_FAILURE);
//		}
		if (dup2(data->outfile, STDOUT) == -1)
			exit_failure(data, "write outfile", DUP2, EXIT_FAILURE);
//		{
//			log_error("write outfile", DUP2);
//			release_resources_and_exit(data, EXIT_FAILURE);
//		}
		close(data->fd[0]);
		close(data->outfile);
	}
	close_fd(data);
	go_to_process(data, data->av[process + 2]);
//	release_resources_and_exit(data, EXIT_SUCCESS);
	close_and_free(data);
	exit(EXIT_SUCCESS);
}

/* */
int	pipex(t_pipex *data)
{
	pid_t	pid[2];
	int		i;

	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(data, i);
		if (pid[i] == -1)
			exit_failure(data, NULL, FORK, EXIT_FAILURE);
//		{
//			log_error(NULL, FORK);
//			release_resources_and_exit(data, EXIT_FAILURE);
//		}
		i++;
	}
	close_fd(data);
	data->status = wait_processes(pid);
	return (data->status);
}
