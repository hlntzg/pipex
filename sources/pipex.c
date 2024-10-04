/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/04 13:51:00 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * child_process - Prepares the child process for execution by opening files,
 * duplicating file descriptors, and closing unnecessary ones.
 * @data: Pointer to the t_pipex structure containing program data.
 * @process: Indicates whether this is the first (0) or second (1) child process.
 *
 * This function will open the appropriate input/output files, set up 
 * the standard input/output for the child process using dup2, and close 
 * any file descriptors that are no longer needed before executing the command.
 */
static void	child_process(t_pipex *data, int process)
{
	if (process == 0)
	{
		open_file(data, process);
		if (dup2(data->infile, STDIN) == -1)
			exit_failure(data, "read infile", DUP2, EXIT_FAILURE);
		if (dup2(data->fd[1], STDOUT) == -1)
			exit_failure(data, "pipe write", DUP2, EXIT_FAILURE);
		close(data->infile);
		close(data->fd[1]);
	}
	else
	{
		open_file(data, process);
		if (dup2(data->fd[0], STDIN) == -1)
			exit_failure(data, "pipe read", DUP2, EXIT_FAILURE);
		if (dup2(data->outfile, STDOUT) == -1)
			exit_failure(data, "write outfile", DUP2, EXIT_FAILURE);
		close(data->fd[0]);
		close(data->outfile);
	}
	close_fd(data);
	go_to_process(data, data->av[process + 2]);
	exit_success(data, EXIT_SUCCESS);
}

/**
 * wait_processes - Waits for both child processes to finish execution.
 * @pid: Array of process IDs for the child processes.
 *
 * This function waits for each child process to terminate and retrieves 
 * their exit status. It returns the exit status of the last terminated 
 * child process or an error code if there was an issue.
 *
 * Return: The exit status of the last terminated child process.
 */
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

/**
 * pipex - Main function to handle the piping between two commands.
 * @data: Pointer to the t_pipex structure containing program data.
 *
 * This function forks two child processes. Each child prepares its 
 * environment using child_process() and executes a command. The parent 
 * process waits for both children to finish execution and retrieves 
 * their exit statuses.
 *
 * Return: The exit status of the last executed command.
 */
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
		i++;
	}
	close_fd(data);
	data->status = wait_processes(pid);
	return (data->status);
}
