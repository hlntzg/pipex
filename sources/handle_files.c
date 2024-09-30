/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:39:33 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/30 11:39:45 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function checks if the file exits (F_OK) and, for READ mode, it checks
 * if it is readable (R_OK) or for WRITE mode, if it is writable (W_OK). */
void	access_file(char *filename, t_fd mode)
{
	if (mode == READ)
	{
		if (access(filename, F_OK) == -1)
			log_error(filename, EXISTENCE);
		else if (access(filename, R_OK) == -1)
			log_error(filename, PERMISSION);
	}
	if (mode == WRITE)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
			log_error(filename, PERMISSION);
	}
}

/* This function handles the opening of the infile (read-only) and outfile 
 * (write-only or, if doesn't exist, created it with permissions 0644). */
void	open_file(t_pipex *data, int process)
{
	char	*filename;
		
	if (process == 0)
	{
		filename = data->av[1];
//		access_file(filename, READ);
		if (access(filename, F_OK) == -1)
			log_error(filename, EXISTENCE);
		else if (access(filename, R_OK) == -1)
			log_error(filename, PERMISSION);
		data->infile = open(filename, O_RDONLY);
	//	if (data->infile == -1)
	//		error for open()?			
	}
	else
	{
		filename = data->av[4];
//		access_file(filename, WRITE);
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
			log_error(filename, PERMISSION);
		data->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//	if (data->outfile == -1)
	//		error for open()?
	}
}

/* For PIPE - it closes the read and write ends of the pipe (data->fd) and frees
 * the allocated memory. Sets data->fd to NULL to prevent dangling pointers. 
 * For FILES - it closes the open files. */
void	close_fd(t_pipex *data)
{
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
