/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:55:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/26 18:15:01 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	log_guide_instructions(void)
{
	ft_putstr_fd("\nguide for execute the program:"
		"\n\t./pipex <file1> <cmd1> <cmd2> <file2>\n"
		"\n\tfile1, file2\t: file names, infile and outfile;"
		"\n\tcmd1, cmd2\t: shell commands with respective parameters;"
		"\n", STDOUT);
}

void	log_error(char *str, t_error type)
{
	ft_putstr_fd("pipex: ", STDERR);
	if (str)
		ft_putstr_fd(str, STDERR);
	if (type == ARGUMENTS)
		ft_putstr_fd(": Incorrect number of arguments", STDERR);
	if (type == EXISTENCE)
		ft_putstr_fd(": No such file or directory", STDERR);
	if (type == PERMISSION)
		ft_putstr_fd(": Permission denied", STDERR);
	if (type == COMMAND)
		ft_putstr_fd(": command not found", STDERR);
	if (type == MALLOC)
		ft_putstr_fd(": memory allocation failed", STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(1);
}

void	release_resources_and_exit(t_pipex *data, int code)
{
	freeeeeee
	exit(code);
}
