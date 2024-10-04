/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:04:24 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/04 13:34:37 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * get_abs_path - Build an absolute path from a directory path and a command.
 * @path: The directory path where the command is located.
 * @cmd: The command to be executed.
 *
 * This function creates an absolute path by concatenating the directory path,
 * a '/' separator, and the command. If the directory path is empty, it returns
 * a duplicate of the command.
 *
 * Return: A pointer to the absolute path string, or NULL on failure.
 */
static char	*get_abs_path(const char *path, const char *cmd)
{
	char	*abs_path;
	size_t	len_path;
	size_t	len_cmd;

	if (*path == '\0')
		return (ft_strdup(cmd));
	len_path = ft_strlen(path);
	len_cmd = ft_strlen(cmd);
	abs_path = (char *)malloc(sizeof(char) * (len_path + len_cmd + 2));
	if (!abs_path)
		return (NULL);
	ft_strlcpy(abs_path, path, len_path + 1);
	ft_strlcat(abs_path, "/", len_path + 2);
	ft_strlcat(abs_path, cmd, len_path + len_cmd + 2);
	return (abs_path);
}

/**
 * execute_command - Attempts to execute a command by building its absolute path.
 * @path: The directory path where the command is located.
 * @command: The command string to be executed.
 * @data: Pointer to t_pipex structure containing program data.
 *
 * This function checks if the absolute path exists and is executable.
 * If so, it attempts to execute the command using execve. It returns a status
 * code indicating success or failure.
 *
 * Return: Status code indicating success or failure of command execution.
 */
static int	execute_command(char *path, char *command, t_pipex *data)
{
	int		status;
	char	**args;
	char	*abs_path;

	args = ft_split(command, ' ');
	if (!args)
		exit_failure(data, "ft_split() on execute_command()",
			MALLOC, EXIT_FAILURE);
	abs_path = get_abs_path(path, args[0]);
	if (!abs_path)
		exit_failure(data, "ft_split() on get_abs_path()",
			MALLOC, EXIT_FAILURE);
	if (access(abs_path, F_OK | X_OK) == 0)
	{
		if (execve(abs_path, args, data->envp) == -1)
			status = CMD_EXEC_ERROR;
		else
			status = CMD_SUCCESS;
	}
	else
		status = CMD_FAIL;
	free_char_double_pointer(args);
	free(abs_path);
	return (status);
}

/**
 * invalid_cmd_arg - Checks if a command argument is valid.
 * @cmd: The command string to check.
 *
 * This function verifies whether a given command string is valid. 
 * It checks for NULL or empty strings and ensures that at least one 
 * printable character exists that is not whitespace.
 *
 * Return: 1 if invalid; 0 if valid.
 */
int	invalid_cmd_arg(char *cmd)
{
	int	i;

	if (!cmd || cmd[0] == '\0')
		return (1);
	i = 0;
	while (cmd[i])
	{
		if (ft_isprint(cmd[i]) && !ft_iswhitespace(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * go_to_process - Executes a given command by searching through available paths.
 * @data: Pointer to t_pipex structure containing program data.
 * @command: The command string to execute.
 *
 * This function checks for valid environment variables and commands,
 * then attempts to execute the specified command either directly or 
 * by searching through available paths. It handles errors appropriately 
 * if execution fails.
 */
void	go_to_process(t_pipex *data, char *command)
{
	int	status;
	int	i;

	if (data->envp == NULL)
		exit_failure(data, NULL, 0, EXIT_FAILURE);
	if (invalid_cmd_arg(command))
		exit_failure(data, command, COMMAND, EXIT_CMD_NOT_FOUND);
	if (ft_strchr(command, '/'))
		status = execute_command("", command, data);
	else if (data->path != NULL)
	{
		i = 0;
		while (data->path && data->path[i])
		{
			status = execute_command(data->path[i], command, data);
			if (status == CMD_SUCCESS || status == CMD_EXEC_ERROR)
				break ;
			i++;
		}
	}
	else
		status = CMD_FAIL;
	if (status == CMD_FAIL || status == CMD_EXEC_ERROR)
		cmd_error_handling(data, command);
}
