/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:49:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/03 15:19:10 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"	/* libft library */
# include <unistd.h>			/* fork, pipe, r/w file, close, dup2, execve */
# include <sys/wait.h>			/* waitpid, wait */
# include <fcntl.h>			/* open */
# include <sys/types.h>			/* pid_t data type */

/* Standard file descriptor definitions */
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* Command execution status codes:
 * CMD_SUCCESS - Command executed successfully
 * CMD_FAIL -Command failed to execute (not found or invalid
 * CMD_EXEC_ERROR - Error during command execution (execve failed) */
# define CMD_SUCCESS 1
# define CMD_FAIL 0
# define CMD_EXEC_ERROR -1

/* Command-related exit codes */
# define EXIT_CMD_NOT_EXECUTABLE 126
# define EXIT_CMD_NOT_FOUND 127

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**envp;
	char	**path;
	char	**cmd;
	int		*fd;
	int		infile;
	int		outfile;
	int		status;
}	t_pipex;

typedef enum s_error
{
	ARGUMENTS,
	MALLOC,
	PIPE,
	FORK,
	DUP2,
	EXISTENCE,
	PERMISSION,	
	COMMAND,
	DIRECTORY,
}	t_error;

/* Main functions to handle piping between commands and execute them */
int		pipex(t_pipex *data);
void	initialize_pipex(int argc, char **argv, char **envp, t_pipex *data);
void	go_to_process(t_pipex *data, char *command);

/* Funtions to handle file and file descriptors associated with pipes */
void	access_file(t_pipex *data, char *filename, int process);
void	open_file(t_pipex *data, int process);
void	close_fd(t_pipex *data);
void	close_and_free(t_pipex *data);

/* Functions to log general and error messages and handle program exit */
void	log_guide_instructions(void);
void	log_error(char *str, t_error type);
void	cmd_error_handling(t_pipex *data, char *cmd);
void	exit_failure(t_pipex *data, char *str, t_error type, int code);
void	exit_success(t_pipex *data, int code);

#endif
