/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:17:04 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/04 11:50:58 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * main - Entry point of the pipex program.
 * @argc: Argument count from command line.
 * @argv: Argument vector from command line.
 * @envp: Environment variables passed to the program.
 *
 * This function checks the number of command-line arguments, initializes 
 * the pipex structure, executes the pipex process, and cleans up resources 
 * before exiting. It returns the exit status of the pipex process.
 */
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
