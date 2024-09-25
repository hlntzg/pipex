/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/25 13:19:20 by hutzig           ###   ########.fr       */
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

void	close_fd(t_pipex *data)
{
	if (data->fd[0] > -1)
		close(data->fd[0]);
	if (data->fd[1] > -1)
		close(data->fd[1]);
	free(data->fd);
	data->fd = NULL;
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
		if (data->infile == -1)
		{
			perror("Error opening infile"); // ERROR;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		file = data->av[4];
		if (access(file, W_OK) == -1)
		{
			perror("Error accessing outfile"); // ERROR;
			exit(EXIT_FAILURE);
		}
		data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile == -1)
		{
			perror("Error opening outfile"); // ERROR;
			exit(EXIT_FAILURE);
		}
	}
}

void	wait_children_processes(t_pipex *data, pid_t *pid, int *status)
{
	int	i;

	(void) data;
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

char	*get_abs_path(char *path, char *cmd)
{
	char	*abs_path;
	char	len_path;
	char	len_cmd;

	if (path)
	{
		len_path = ft_strlen(path);
		len_cmd = ft_strlen(cmd);
		abs_path = (char *)malloc(sizeof(char) * (len_path + len_cmd + 2));
		if (!abs_path)
			return (NULL);
		ft_strlcpy(abs_path, path, len_path + 1);
		ft_strlcat(abs_path, "/", len_path + 2);
		ft_strlcat(abs_path, cmd, len_path + len_cmd + 2);
	}
	else
		abs_path = ft_strdup(cmd);
	return (abs_path);
}

int	execute_command(char *path, char *command, t_pipex *data)
{
	int	status;
	char	**cmd_args;
	char	*abs_path;

	status = CMD_FAIL;
	cmd_args = ft_split(command, ' ');
	if (!cmd_args)
	{
		//error 
		return (CMD_FAIL);
	}
	abs_path = get_abs_path(path, cmd_args[0]);
	if (!abs_path)
	{
		//free_array(cmd_args);
		//error;
		return (CMD_FAIL);
	}
	if (access(abs_path, F_OK) == 0)
	{
		if (access(abs_path, X_OK) == 0)
		{
			if (execve(abs_path, cmd_args, data->envp) == -1)
				status = CMD_EXEC_ERROR;
			else
				status = CMD_SUCCESS;
		}
	}
//	free_array(cmd_args);
	free(abs_path);
	return (status);
}

void	go_to_process(t_pipex *data, char *command)
{
	int	status;
	int	i;

	if (command[0] == '\0' || !command)
		// error
	status = CMD_FAIL;
	if (command[0] == '/' || command[0] == '.' || ft_strchr(command, '/'))
		status = execute_command("", command, data);
	else
	{
		i = 0;
		while (data->path && data->path[i])
		{
			status = execute_command(data->path[i], command, data);
			if (status == CMD_SUCCESS || status == CMD_EXEC_ERROR)
				break ;
			i++;
		}
	}
	if (status == CMD_FAIL || status == CMD_EXEC_ERROR)	
		// if fails, msg and exit the child process @ cmd_error(command, data); 
		printf("error");
}

/* This function open the specific file, duplicate the file descriptors and 
 * close them before calling the execute_cmds(). */
void	child_process(t_pipex *data, int process)
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
	//	data->outfile = open_file(data, process);
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
	exit(EXIT_SUCCESS); // work on this function 
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
	free(data->fd);
	return (get_exit_code(status));
}

