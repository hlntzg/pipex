/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/23 15:14:55 by hutzig           ###   ########.fr       */
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

/* This function open the files. Infile has already been checked for existence
 * and accessibility in access_infile();. */
void	open_file(t_pipex *data, int process)
{
	char	*file;
		
	if (process == 0)
	{
		file = data->av[1];
		data->infile = open(file, O_RDONLY);
	}
	else
	{
		file = data->av[4];
		if (access(file, W_OK) == -1)
		//	error ();
		data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (data->infile == -1 | data->outfile == -1)
		//	error on open();
}

void	wait_children_processes(t_pipex *data, pid_t *pid, int *status)
{
	int	i;

	i = 0;
	while (i < 2)
		waitpid(pid[i++], status, 0);
	// do we need to handle error if waitpid() fails in each iteration?
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

void	execute_process(t_pipex *data, char *command)
{
	char	**cmd_args;
	char	*cmd_path;
	int	status;

	if (command[0] == '\0' || !command)
		// error
	if (command[0] == '/' || command[0] == '.')
	{
		cmd_path = command;
		status = execute_command();// Direct execution
	}
	else
	{
		//cmd_path = get_abs_path(cmd_args[0], data->envp);
		cmd_args = ft_split(command, ' ');
		if (!cmd_args)
			// error if Malloc fails
		while (data->path && data->path[i])
		{
			status = execute_command();//execve(abs_cmd_path, cmd_args, data->envp);
			if (status == CMD_SUCCESS || status == CMD_EXEC_ERROR)
				break ;
			i++;
		}
	}
	if (status == CMD_FAIL || status == CMD_EXEC_ERROR)	
		// if fails, msg and exit the child process @ cmd_error(command, data); 
	free_stuff // Free dynamically allocated memory (cmd_args) only if it was allocated
}

/* This function open the specific file, duplicate the file descriptors and 
 * close them before calling the execute_cmds(). */
void	child_process(t_pipex *data, int process)
{
	if (process == 0)
	{
		open_file(data, process);
		if (dup2(data->infile, STDIN) == -1)
		//	error ();
		if (dup2(data->fd[1], STDOUT) == -1)
		//	error ();
		close(data->infile);
		close(data->fd[1]);
	}
	else
	{
		data->outfile = open_file(data, process);
		if (dup2(data->fd[0], STDIN) == -1)
		//	error ();
		if (dup2(data->outfile, STDOUT) == -1)
		// 	error ();
		close(data->fd[0]);
		close(data->outfile);
	}
	close_fd(data);
	execute_process(data, data->av[process + 2]); // work on this function
	exit(0); // work on this function 
}

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
