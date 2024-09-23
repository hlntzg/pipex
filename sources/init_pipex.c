/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:54:15 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/23 11:34:54 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(t_pipex *data, char **envp)
{
	char	**path;
	(void)data;

	if (!(*envp))
		return (NULL); // return some error ?
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	path = ft_split((*envp) + 5, ':');
	if (!path)
		return (NULL); // check malloc fails, any other error?
	return (path);
}

int	*get_pipe_fd(t_pipex *data)
{
	int	*fd;
	(void)data;

	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return (NULL); // check mallocs fails, return any error?
	if (pipe(fd) == -1)
	{
		free(fd);
		log_error("Error on pipe()::(get_pipe_fd())");
	}
	return (fd);
}

void	init_pipex_data(int argc, char **argv, char **envp, t_pipex *data)
{
	data->ac = argc;
	data->av = argv;
	data->envp = envp;
	data->path = get_path(data, envp);
	data->fd = get_pipe_fd(data);
	//data->cmds = argc - 3;
}
