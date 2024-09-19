/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:17:04 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/19 12:24:01 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_path(t_pipex *data, char **envp)
{
	if (!(*envp))
		return ;
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	data->path = ft_split((*envp) + 5, ':');
	if (!data->path)
		return ; // check malloc fails, any other error?
}

void	init_pipex_data(int argc, char **argv, char **envp, t_pipex *data)
{
	data->ac = argc;
	data->av = argv;
	data->envp = envp;
	data->path = NULL;
	data->fd = NULL;
	get_path(data, envp);
}

int	main(int argc, char **argv, char **envp) // # envp: the environmental variable
{
	t_pipex	data;

	if (argc != 5)
	{
		log_error("Error: Incorrect number of arguments");
		log_guide();
		return (EXIT_FAILURE);
	}
	init_pipex_data(argc, argv, envp, &data);
	//ft_putstr_fd("working pipex program", 1);
	return (EXIT_SUCCESS);
}
