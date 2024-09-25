/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:17:04 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/25 16:21:29 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int	status;

	if (argc != 5)
	{
		log_error("follow the instructions", 1);
		log_guide_instructions();
		return (EXIT_FAILURE);
	}
	access_infile(argv[1]);
	init_pipex_data(argc, argv, envp, &data);
	status = pipex(&data);
//	free(&data);
	return (status);
}
