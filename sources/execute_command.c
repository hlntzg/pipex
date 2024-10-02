/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:04:24 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/02 09:44:44 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_abs_path(char *path, char *cmd)
{
	char	*abs_path;
	char	len_path;
	char	len_cmd;

	if (ft_strncmp(&path[0], "", 1) == 0)
		abs_path = ft_strdup(cmd);
	else
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
	return (abs_path);
}

int	execute_command(char *path, char *command, t_pipex *data)
{
	int		status;
	char	**args;
	char	*abs_path;

	status = CMD_FAIL;
	args = ft_split(command, ' ');
	if (!args)
	{
		log_error("ft_split() on execute_command()", MALLOC);
		release_resources_and_exit(data, EXIT_FAILURE);
	}
	abs_path = get_abs_path(path, args[0]);
	if (!abs_path)
	{
		log_error("malloc() on get_abs_path()", MALLOC);
		release_resources_and_exit(data, EXIT_FAILURE);
	}
	if (access(abs_path, F_OK) == 0)
	{
		if (access(abs_path, X_OK) == -1)
			status = CMD_EXEC_ERROR;
		else
		{
			if (execve(abs_path, args, data->envp) == -1)
				status = CMD_EXEC_ERROR;
			else
				status = CMD_SUCCESS;
		}
	}
	else
		status = CMD_FAIL;
	free_char_double_pointer(args);
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
		release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
	}
	if (ft_strchr(command, '/'))
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

/* checks for no path, than for the existence of the file (if has '/' is folder
 * or invalid cmd path (exit code for cmd1 is 0, cmd2 is 127), else is invalid
 * cmd and has the same exit codes). If the file exists, it is executable and
  * if has '\' its a folder - exit code 126. At this point, if none condition
 * is reached, so it doesnt have execution permitions and gets exit code 126.*/
void	cmd_errors(t_pipex *data, char *cmd)
{
	if ((ft_strncmp(data->path[0], "", 1) == 0))
	{		
		log_error(cmd, EXISTENCE);
		release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
	}
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			log_error(cmd, EXISTENCE);
			release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
		}
		else
		{
			log_error(cmd, COMMAND);
			release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
		}
	}
	if (access(cmd, X_OK) == 0 && ft_strchr(cmd, '/'))
	{
		log_error(cmd, DIRECTORY);
		release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
	}
	log_error(cmd, PERMISSION);
	release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
}
/*{
	if ((ft_strncmp(data->path[0], "", 1) == 0) || (access(cmd, F_OK) == -1 && ft_strchr(cmd, '/')))
	{
		log_error(cmd, EXISTENCE); 
		release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
	{
		if (ft_strchr(cmd, '/'))
		{
			log_error(cmd, DIRECTORY);
			release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
		}
		else
		{
			log_error(cmd, COMMAND);
			release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
		}
	}
	if (access(cmd, X_OK) == -1 && *cmd == '/')
	{
		log_error(cmd, EXISTENCE);
		release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
	}
	if (access(cmd, X_OK) == -1 && !ft_strchr(cmd, '/'))
	{
		log_error(cmd, COMMAND);
		release_resources_and_exit(data, EXIT_CMD_NOT_FOUND);
	}
	log_error(cmd, PERMISSION);
	release_resources_and_exit(data, EXIT_CMD_NOT_EXECUTABLE);
}*/
