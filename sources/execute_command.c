/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:04:24 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/27 19:00:33 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_abs_path(char *path, char *cmd)
{
	char	*abs_path;
	char	len_path;
	char	len_cmd;

	if (path)
	{
		len_path = ft_strlen(path);
		len_cmd = ft_strlen(cmd);
		abs_path = (char *)malloc(sizeof(char) * (len_path + len_cmd + 2));
		if (!abs_path)
			return (NULL);
		ft_strlcpy(abs_path, path, len_path + 1);
		ft_strlcat(abs_path, "/", len_path + 2);
		ft_strlcat(abs_path, cmd, len_path + len_cmd + 2);
	}
	else
		abs_path = ft_strdup(cmd);
	return (abs_path);
}

int	execute_command(char *path, char *command, t_pipex *data)
{
	int	status;
	char	**cmd_args;
	char	*abs_path;

	status = CMD_FAIL;
	cmd_args = ft_split(command, ' ');
	if (!cmd_args)
	{
		//error 
	}
	abs_path = get_abs_path(path, cmd_args[0]);
	if (!abs_path)
	{
		//free_array(cmd_args);
		//error;
	}
	if (access(abs_path, F_OK) == 0)
	{
		if (access(abs_path, X_OK) == 0)
		{
			if (execve(abs_path, cmd_args, data->envp) == -1)
				status = CMD_EXEC_ERROR;
			else
				status = CMD_SUCCESS;
		}
	}
//	free_array(cmd_args);
	free(abs_path);
	return (status);
}

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

void	go_to_process(t_pipex *data, char *command)
{
	int	status;
	int	i;

	if (invalid_cmd_arg(command))
	{
		log_error(command, COMMAND);
		release_resources_and_exit(data, FAILURE);
	}
	if (command[0] == '/' || command[0] == '.' || ft_strchr(command, '/'))
		status = execute_command("", command, data);
	else
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
	if (status == CMD_FAIL || status == CMD_EXEC_ERROR)
		cmd_error(data, command);
}

void	cmd_errors(t_pipex *data, char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		log_error(cmd, EXISTENCE);
		release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
	}
	if (access(cmd, X_OK) == -1)
	{
		if (*cmd == '/')
			log_error(cmd, PERMISSION);	// permission denied for absolute path
		else //if (!ft_strchr(cmd, '/'))
			log_error(cmd, COMMAND);	// command not found in path
		release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
	}
	if (ft_strchr(cmd, '/'))
	{
		log_error(cmd, DIRECTORY);		// attempting to execute a directory
		release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
	}
	log_error(cmd, COMMAND);			// command found but not executable
	release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
}
