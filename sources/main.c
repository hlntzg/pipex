/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:17:04 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/19 15:59:27 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp) // # envp: the environmental variable
{
	t_pipex	data;
	int	status = 0;

	if (argc != 5)
	{
		log_error("Error: Incorrect number of arguments");
		log_guide();
		return (EXIT_FAILURE);
	}
	init_pipex_data(argc, argv, envp, &data);
//	status = pipex(&data);
	return (status);
	//return (EXIT_SUCCESS);
}
