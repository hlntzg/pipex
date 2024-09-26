/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:54:15 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/26 18:17:38 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	**path;

	if (!envp || !*envp)
	{
		ft_putstr_fd("pipex: envp is invalid or empty\n", STDERR);
		return (NULL);
	}
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!(*envp))
	{
		ft_putstr_fd("pipex: PATH environment variable not found\n", STDERR);
		path = ft_split("", 0);
	}
	else
		path = ft_split((*envp) + 5, ':');
	if (!path)
	{
		perror("pipex: gat_path(): memory allocation failed\n");
		return (NULL);
	}
	return (path);
}	

static int	*get_pipe_fd(t_pipex *data)
{
	int	*fd;
	(void)data;

	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
	{
		log_error("get_pipe_fd()", MALLOC);
		release_resources_and_exit(data, FAILURE);
		//perror("Memory allocation failed in get_pipe_fd()");
		//return (NULL); // check mallocs fails, return any error?
	}
	if (pipe(fd) == -1)
	{
		free(fd);
		log_error(NULL, PIPE);
		release_resources_and_exit(data, FAILURE);
		//perror("Error on pipe()::(get_pipe_fd())");
		//return (NULL);
	}
	return (fd);
}

void	initialize_pipex(int argc, char **argv, char **envp, t_pipex *data)
{
	data->ac = argc;
	data->av = argv;
	data->envp = envp;
	data->fd = get_pipe_fd(data);
}
