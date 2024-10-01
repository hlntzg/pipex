/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:39:33 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/01 17:04:35 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function checks if the file exits (F_OK) and, for READ mode, it checks
 * if it is readable (R_OK) or for WRITE mode, if it is writable (W_OK). */
void	access_file(t_pipex *data, char *filename, int process)
{
	if (process == 0)
	{
		if (access(filename, F_OK) == -1)
		{
			log_error(filename, EXISTENCE);
			release_resources_and_exit(data, EXIT_FAILURE);
		}
		else if (access(filename, R_OK) == -1)
		{
			log_error(filename, PERMISSION);
			release_resources_and_exit(data, EXIT_FAILURE);
		}	
	}
	else
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
		{
			log_error(filename, PERMISSION);
			release_resources_and_exit(data, EXIT_FAILURE);
		}
	}
}

/* This function handles the opening of the infile (read-only) and outfile 
 * (write-only or, if doesn't exist, created it with permissions 0644). */
void	open_file(t_pipex *data, int process)
{
	if (process == 0)
	{
		access_file(data, data->av[1], process);
		data->infile = open(data->av[1], O_RDONLY);
		if (data->infile == -1)
		{
			log_error(data->av[1], EXISTENCE);
			release_resources_and_exit(data, EXIT_FAILURE);
		}
	}
	else
	{
		access_file(data, data->av[4], process);
		data->outfile = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile == -1)
		{
			log_error(data->av[4], EXISTENCE);
			release_resources_and_exit(data, EXIT_FAILURE);
		}
	}
}

/* This function closes the read and write ends of the pipe (data->fd) and frees
 * the allocated memory. Sets data->fd to NULL to prevent dangling pointers. */
void	close_fd(t_pipex *data)
{
	if (!data->fd)
		return ;
	if (data->fd[0] > -1)
		close(data->fd[0]);
	if (data->fd[1] > -1)
		close(data->fd[1]);
	free(data->fd);
	data->fd = NULL;
}

void	close_file(t_pipex *data)
{
	if (data->infile > -1)
		close(data->infile);
	if (data->outfile > -1)
		close(data->outfile);
}
