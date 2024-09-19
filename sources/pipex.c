/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/19 18:19:16 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function check the accessibility for reading (F_OK) and F_OK tests for
 * the existence of the file. */
void	access_infile(char *file)
{
	if (access(file, R_OK) == -1 && errno == EACCES)
 	{
		// "Permission denied\n" ----- handle error
		return (EXIT_FAILURE);
	}
	if (access(file, F_OK) == -1 && errno == ENOENT)
	{
		// "No such file file or directory\n" ---- handle error
		return (EXIT_FAILURE);
	}
}

int	pipex(t_pipex *data)
{


}
