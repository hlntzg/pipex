/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:49:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/23 11:37:03 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include <stdio.h>			///// PRINTF, REMOVE BEFORE SUBMISSION


# include "../lib/libft/libft.h"	/* libft library */
# include <unistd.h>			/* fork, pipe, r/w file, close, dup2, execve */
# include <string.h>			/* sterror */
# include <sys/wait.h>			/* waitpid, wait */
# include <errno.h>			/* errno */
# include <fcntl.h>			/* open */
# include <sys/types.h>			/* pid_t data type */

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
//	int	cmds;
}	t_pipex;


void	log_guide(void);
void	log_error(char *str);


char	**get_path(t_pipex *data, char **envp);
int	*get_pipe_fd(t_pipex *data);
void	init_pipex_data(int argc, char **argv, char **envp, t_pipex *data);
void	access_infile(char *file);
int	pipex(t_pipex *data);
void	close_fd(t_pipex *data);

#endif
