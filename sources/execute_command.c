/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:04:24 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/30 14:27:36 by hutzig           ###   ########.fr       */
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
		log_error("ft_split() on execute_command()", MALLOC);
		release_resources_and_exit(data, FAILURE); 
	}
	abs_path = get_abs_path(path, cmd_args[0]);
	if (!abs_path)
	{
		log_error("malloc() on get_abs_path()", MALLOC);
		release_resources_and_exit(data, FAILURE);
	}
	if (access(abs_path, F_OK) == 0)
	{
		if (execve(abs_path, cmd_args, data->envp) == 0)
			status = CMD_SUCCESS;
		else if (access(abs_path, X_OK) == -1)
			status = CMD_EXEC_ERROR;
	}
	free_char_double_pointer(cmd_args);
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
		log_error(command, COMMAND); // test 14, 15, 16
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
		cmd_errors(data, command);
}

void	cmd_errors(t_pipex *data, char *cmd)
{
	if (access(cmd, F_OK) == -1) // check for the existence of the file
	{
		// IS FOLDER (7, 8
		// INVALID CMD (PATH) (10, 12, 13
		if (ft_strchr(cmd, '/'))
		{
			log_error("A", EXISTENCE); 
			release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
		}
		// INVALID CMD (9, 11, 13
		/////// wrong (19) PATH ENVP DOES NOT EXIST 	should be "no such file or directory"
		/////// wrong (20) NO PATH ENVP, CMD1 (PATH) 	should be "no such file or directory"
		else
		{
			log_error("B", COMMAND);
			release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
		}
	}
	if (access(cmd, X_OK) == -1 && *cmd == '/')
	{
		log_error("C", EXISTENCE);
		release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
	}
	if (access(cmd, X_OK) == -1 && ft_strchr(cmd, '/') == NULL)
	{
		log_error("D", COMMAND);
		release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
	{
		if (ft_strchr(cmd, '/'))
		{
			log_error("E", DIRECTORY);
			release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
		}
		else
		{
			log_error("D", COMMAND);
			release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
		}
	}
	// NO EXEC PERMISSION (5, 6)
	log_error("E", PERMISSION);
	release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
}
