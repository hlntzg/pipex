/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:55:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/25 16:08:18 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	log_guide_instructions(void)
{
	ft_putstr_fd("\n\nguide for execute the program:"
		"\n\t./pipex [file1] [cmd1] [cmd2] [file2]\n"
		"\n\tfile1, file2\t: file names, infile and outfile;"
		"\n\tcmd1, cmd2\t: shell commands with respective parameters;"
		"\n", STDOUT);
}

void	log_error(char *msg, int i)
{
	ft_putstr_fd("pipex: ", STDERR);
	if (i == 1)
		ft_putstr_fd("incorrect number of arguments: ", STDERR);
	if (msg)
		ft_putstr_fd(msg, STDERR);
}
