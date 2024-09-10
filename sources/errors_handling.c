/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:55:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/10 11:11:48 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	log_error(char *str)
{
	ft_putstr_fd("\033[0;31m", 1);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("\033[0m", 1);
}

void	log_guide(void)
{
	ft_putstr_fd("\nGuide for pipex usage:"
		"\n\t./pipex [file1] [cmd1] [cmd2] [file2]\n"
		"\nfile1 and file2 : file names;"
		"\ncmd1 and cmd2 : shell commands with respective parameters;"
		"\n\n", 1);
}
