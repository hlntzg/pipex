/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:17:04 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/01 16:52:52 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		status;

	if (argc != 5)
	{
		log_error("Error", ARGUMENTS);
		log_guide_instructions();
		return (EXIT_FAILURE);
	}
	initialize_pipex(argc, argv, envp, &data);
	status = pipex(&data);
	close_and_free(&data);
	return (status);
}
