/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:17:04 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/26 17:29:18 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int	status;

	if (argc != 5)
	{
		log_error("Error", ARGUMENTS);
		log_guide_instructions();
		return (EXIT_FAILURE);
	}
	data.path = get_path(envp);
	if (!data.path)
		return (EXIT_FAILURE);
	initialize_pipex(argc, argv, envp, &data);
	status = pipex(&data);
//	free(&data);
	return (status);
}
