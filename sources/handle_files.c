/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:39:33 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/25 17:11:11 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function checks if infile exits (F_OK) and is readable (R_OK). 
 * Exits the program on failure. */
void	access_infile(char *file)
{
	if (access(file, F_OK | R_OK) == -1) 
 	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);  // ENOENT or EACCES
		exit(EXIT_FAILURE); //exit the program?
	}
}

/* This function handles the opening of the infile (read-only) and outfile 
 * (write-only or, if doesn't exist, created it with permissions 0644). */
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
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
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

/* This function closes the read and write ends of the pipe (data->fd) and frees
 * the allocated memory. Sets data->fd to NULL to prevent dangling pointers. */
void	close_fd(t_pipex *data)
{
	if (data->fd[0] > -1)
		close(data->fd[0]);
	if (data->fd[1] > -1)
		close(data->fd[1]);
	free(data->fd);
	data->fd = NULL;
}
