/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:55:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/25 11:23:39 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	log_error(char *str)
{
	ft_putstr_fd("\033[0;31m", STDOUT);
	ft_putendl_fd(str, STDERR);
	ft_putstr_fd("\033[0m", STDOUT);
}

void	log_guide(void)
{
	ft_putstr_fd("\nGuide for pipex usage:"
		"\n\t./pipex [file1] [cmd1] [cmd2] [file2]\n"
		"\n\tfile1, file2\t: file names, infile and outfile;"
		"\n\tcmd1, cmd2\t: shell commands with respective parameters;"
		"\n\n", STDERR);
}
