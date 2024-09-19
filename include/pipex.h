/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:49:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/09/19 15:57:33 by hutzig           ###   ########.fr       */
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

# define STDERR 2
# define STDOUT 1
# define STDIN 0

typedef struct s_pipex
{
	int	ac;
	char	**av;
	char	**envp;
	char	**path;
	int	*fd;
	char	*infile; //check if it will be usefull
	char	*outfile; // same as infile
}	t_pipex;


void	log_guide(void);
void	log_error(char *str);


char	**get_path(t_pipex *data, char **envp);
int	*get_pipe_fd(t_pipex *data);
void	init_pipex_data(int argc, char **argv, char **envp, t_pipex *data);

#endif
