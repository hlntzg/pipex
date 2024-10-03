/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:55:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/03 15:04:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * exit_failure - Logs an error message and cleans up resources before exiting.
 * @data: Pointer to t_pipex structure containing program data.
 * @str: Error message string to log.
 * @type: Type of error that occurred (e.g., memory allocation, file existence).
 * @code: Exit code to return to the operating system.
 *
 * This function logs an error message based on the type of error,
 * closes file descriptors, frees allocated memory, and exits the program
 * with the specified exit code.
 */
void	exit_failure(t_pipex *data, char *str, t_error type, int code)
{
	log_error(str, type);
	close_fd(data);
	free_char_double_pointer(data->path);
	exit(code);
}

void	exit_success(t_pipex *data, int code)
{
	close_and_free(data);
	exit(code);
}

/**
 * log_error - Logs an error message to standard error (STDERR).
 * @str: The specific error message string to log.
 * @type: The type of error that occurred (e.g., arguments, malloc failure).
 *
 * This function prints a standardized error message prefix followed by
 * a specific message based on the type of error. It helps in debugging
 * by providing clear feedback on what went wrong during execution.
 */
void	log_error(char *str, t_error type)
{
	ft_putstr_fd("pipex: ", STDERR);
	if (str)
		ft_putstr_fd(str, STDERR);
	if (type == ARGUMENTS)
		ft_putstr_fd(": Incorrect number of arguments\n", STDERR);
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
	if (type == PIPE)
		ft_putstr_fd(": pipe() failed on get_pipe_fd()\n", STDERR);
	if (type == FORK)
		ft_putstr_fd(": fork() failed on pipex()\n", STDERR);
	if (type == DUP2)
		ft_putstr_fd(": dup2() failed on child_process()\n", STDERR);
}

/**
 * cmd_error_handling - Handles errors related to command execution.
 * @data: Pointer to t_pipex structure containing program data.
 * @cmd: The command string that caused the error.
 *
 * This function checks various conditions to determine why a command
 * could not be executed. It verifies the existence of the command (F_OK),
 * checks if it is executable (X_OK), and handles errors appropriately by
 * calling exit_failure with the relevant error type and exit codes.
 */
void	cmd_error_handling(t_pipex *data, char *cmd)
{
	if (data->path == NULL)
		exit_failure(data, cmd, EXISTENCE, EXIT_CMD_NOT_FOUND);
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			exit_failure(data, cmd, EXISTENCE, EXIT_CMD_NOT_FOUND);
		else
			exit_failure(data, cmd, COMMAND, EXIT_CMD_NOT_FOUND);
	}
	if (access(cmd, X_OK) == 0 && ft_strchr(cmd, '/'))
		exit_failure(data, cmd, DIRECTORY, EXIT_CMD_NOT_EXECUTABLE);
	else if (access(cmd, X_OK) == 0 && !ft_strchr(cmd, '/'))
		exit_failure(data, cmd, COMMAND, EXIT_CMD_NOT_FOUND);
	exit_failure(data, cmd, PERMISSION, EXIT_CMD_NOT_EXECUTABLE);
}

/**
 * log_guide_instructions - Prints usage instructions for executing the program.
 *
 * This function provides a guide on how to run the pipex program,
 * including details about required input files and commands. It helps 
 * users understand how to correctly invoke the program from the command line.
 */
void	log_guide_instructions(void)
{
	ft_putstr_fd("\nguide for execute the program:"
		"\n\t./pipex <file1> <cmd1> <cmd2> <file2>\n"
		"\n\tfile1, file2\t: file names, infile and outfile;"
		"\n\tcmd1, cmd2\t: shell commands with respective parameters;"
		"\n", STDERR);
}
