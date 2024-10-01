/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:54:15 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/01 16:53:32 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	**path;

	path = NULL;
	if (!envp || !*envp)
	{
		log_error(NULL, ENVP);
		return (path);
	}
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!(*envp))
	{
		log_error(NULL, PATH);
		path = ft_split("", 0);
	}
	else
		path = ft_split((*envp) + 5, ':');
	if (!path)
	{
		log_error("ft_split() on get_path()", MALLOC);
		return (NULL);
	}
	return (path);
}	

static int	*get_pipe_fd(t_pipex *data)
{
	int	*pipefd;

	pipefd = (int *)malloc(sizeof(int) * 2);
	if (!pipefd)
	{
		log_error("malloc() on get_pipe_fd()", MALLOC);
		release_resources_and_exit(data, EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		free(pipefd);
		log_error(NULL, PIPE);
		release_resources_and_exit(data, EXIT_FAILURE);
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
