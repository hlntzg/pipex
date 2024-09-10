/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:17:04 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/10 11:40:59 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp) // envp ??
{
	(void)argv;
	(void)envp;
	if (argc != 5)
	{
		log_error("Error: Incorrect number of arguments");
		log_guide();
		return (EXIT_FAILURE);
	}
	ft_putstr_fd("working pipex program", 1);
	return (EXIT_SUCCESS);
}
