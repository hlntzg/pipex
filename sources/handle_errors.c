/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:55:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/01 11:22:26 by hutzig           ###   ########.fr       */
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
		ft_putstr_fd(": Incorrect number of arguments\n", STDERR);
	if (type == ENVP)
		ft_putstr_fd(": envp is invalid or empty\n", STDERR);
	if (type == PATH)
		ft_putstr_fd(": PATH environment variable not found\n", STDERR);	
	if (type == MALLOC)
		ft_putstr_fd(": memory allocation failed\n", STDERR);
	if (type == EXISTENCE)
		ft_putstr_fd(": No such file or directory\n", STDERR);
	if (type == PERMISSION)
		ft_putstr_fd(": Permission denied\n", STDERR);
	if (type == COMMAND)
		ft_putstr_fd(": command not found\n", STDERR);
	if (type == DIRECTORY)
		ft_putstr_fd(": Is a directory\n", STDERR);
	if (type == PIPE) //errno
		ft_putstr_fd(": pipe() failed on get_pipe_fd()\n", STDERR); 
	if (type == FORK) //errno
		ft_putstr_fd(": fork() failed on pipex()\n", STDERR);
	if (type == DUP2)  //errno
		ft_putstr_fd(": dup2() failed on child_process()\n", STDERR);
}

void	release_resources_and_exit(t_pipex *data, int code)
{
	close_fd(data);
	close_file(data);
	free_char_double_pointer(data->path);
	exit(code);
}

void	close_and_free(t_pipex *data)
{
	close_file(data);
	close_fd(data);
	free_char_double_pointer(data->path);
}
