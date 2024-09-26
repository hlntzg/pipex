/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:49:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/26 18:18:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"	/* libft library */
# include <unistd.h>			/* fork, pipe, r/w file, close, dup2, execve */
# include <string.h>			/* sterror */
# include <sys/wait.h>			/* waitpid, wait */
# include <errno.h>			/* errno */
# include <fcntl.h>			/* open */
# include <sys/types.h>			/* pid_t data type */
# include <stdio.h>			/* perror */

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define CMD_SUCCESS 1			/* Command executed successfully */
# define CMD_FAIL 0			/* Command failed to execute (not found or invalid) */
# define CMD_EXEC_ERROR -1		/* Error during command execution (execve failed) */

# define SUCCESS 0
# define FAILURE 1

// Command-related exit codes
# define EXIT_CMD_NOT_EXECUTABLE 126
# define EXIT_CMD_NOT_FOUND 127

typedef struct s_pipex
{
	int	ac;
	char	**av;
	char	**envp;
	char	**path;
	char	**cmd;
	int	*fd;
	int	infile;
	int	outfile;
}	t_pipex;

typedef enum s_fd
{
	PIPE,
	FILES,
	READ,
	WRITE,
}	t_fd;

typedef enum s_error
{
	ARGUMENTS,
	EXISTENCE,
	PERMISSION,	
	COMMAND,
	MALLOC,
	PIPE,
}	t_error;

void	log_guide_instructions(void);
void	log_error(char *str, t_error type);


void	open_file(t_pipex *data, int process);
void	access_file(char *filename, t_fd mode);
void	close_fd(t_pipex *data, t_fd fd);

char	**get_path(char **envp);

void	initialize_pipex(int argc, char **argv, char **envp, t_pipex *data);
int	pipex(t_pipex *data);
void	go_to_process(t_pipex *data, char *command);

#endif
