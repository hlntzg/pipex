/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:54:15 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/04 13:52:03 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * get_path - Retrieves the system PATH environment variable.
 * @envp: Array of environment variables passed to the program.
 *
 * This function searches for the "PATH" variable in the environment
 * variables and splits its value into an array of directory paths.
 * 
 * Return: Array of strings representing directories in PATH,
 * or NULL if an error occurs or if PATH is not found.
 */
static char	**get_path(char **envp)
{
	char	**path;

	path = NULL;
	if (!envp || !*envp)
		return (NULL);
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp == NULL)
		return (NULL);
	else
		path = ft_split((*envp) + 5, ':');
	if (!path)
	{
		log_error("ft_split() on get_path()", MALLOC);
		return (NULL);
	}
	return (path);
}

/**
 * get_pipe_fd - Allocates memory for pipe file descriptors and creates a pipe.
 * @data: Pointer to t_pipex structure containing program data.
 *
 * This function allocates memory for two file descriptors (read and write ends)
 * and creates a pipe. If allocation or pipe creation fails, it handles errors 
 * appropriately by logging and exiting.
 *
 * Return: Pointer to an array containing read and write ends of the pipe,
 * or exits on failure.
 */
static int	*get_pipe_fd(t_pipex *data)
{
	int	*pipefd;

	pipefd = NULL;
	pipefd = (int *)malloc(sizeof(int) * 2);
	if (!pipefd)
		exit_failure(data, "malloc() on get_pipe_fd()", MALLOC, EXIT_FAILURE);
	if (pipe(pipefd) == -1)
	{
		free(pipefd);
		exit_failure(data, NULL, PIPE, EXIT_FAILURE);
	}
	return (pipefd);
}

void	initialize_pipex(int argc, char **argv, char **envp, t_pipex *data)
{
	data->ac = argc;
	data->av = argv;
	data->envp = envp;
	data->path = get_path(envp);
	data->fd = get_pipe_fd(data);
}
