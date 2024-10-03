/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:39:33 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/03 14:57:30 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * access_file - Checks the accessibility of a file for reading or writing.
 * @data: Pointer to t_pipex structure containing program data.
 * @filename: Name of the file to check.
 * @process: Indicates whether to check for read (0) or write (1) permissions.
 *
 * This function checks if the specified file exists and if it is readable
 * (for input files) or writable (for output files). If any check fails,
 * it calls exit_failure to handle the error appropriately.
 */
void	access_file(t_pipex *data, char *filename, int process)
{
	if (process == 0)
	{
		if (access(filename, F_OK) == -1)
			exit_failure(data, filename, EXISTENCE, EXIT_FAILURE);
		else if (access(filename, R_OK) == -1)
			exit_failure(data, filename, PERMISSION, EXIT_FAILURE);
	}
	else
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
			exit_failure(data, filename, PERMISSION, EXIT_FAILURE);
	}
}

/**
 * open_file - Handle opening input and output files based on process type.
 * @data: Pointer to t_pipex structure containing program data.
 * @process: Indicates whether to open an input file (0) or an output file (1).
 *
 * This function handles opening the input file in read-only mode and the 
 * output file in write-only mode. If the output file does not exist,
 * it creates it with permissions set to 0644. If any operation fails,
 * it calls exit_failure to handle the error appropriately.
 */
void	open_file(t_pipex *data, int process)
{
	if (process == 0)
	{
		access_file(data, data->av[1], process);
		data->infile = open(data->av[1], O_RDONLY);
		if (data->infile == -1)
			exit_failure(data, data->av[1], EXISTENCE, EXIT_FAILURE);
	}
	else
	{
		access_file(data, data->av[4], process);
		data->outfile = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile == -1)
			exit_failure(data, data->av[4], EXISTENCE, EXIT_FAILURE);
	}
}

/**
 * close_fd - Closes the read and write ends of the pipe and frees memory.
 * @data: Pointer to t_pipex structure containing program data.
 *
 * This function checks if there are any open file descriptors in data->fd,
 * closes them if they are valid, frees the allocated memory for fd,
 * and sets the pointer to NULL to prevent dangling pointers.
 */
void	close_fd(t_pipex *data)
{
	if (!data->fd)
		return ;
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
	free(data->fd);
	data->fd = NULL;
}

void	close_and_free(t_pipex *data)
{
	close_fd(data);
	free_char_double_pointer(data->path);
}
