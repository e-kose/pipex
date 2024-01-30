/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:35:37 by ekose             #+#    #+#             */
/*   Updated: 2024/01/19 18:20:15 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		error_file;
	int		pid1;
	int		pid2;
	int		fd[2];
	char	*path;
	char	**sep_path;
}	t_pipex;

char	*find_path(char **envp);
void	first_child_procces(t_pipex pipex, char **argv, char **envp);
void	second_child_procces(t_pipex pipex, char **argv, char **envp);
char	*cmd_get(char **sep_path, char *cmd_arg);
void	transactions(t_pipex *pipex, int argc, char **argv);
void	err_msg(char *error);
void	msg(char *error);
void	ft_close(t_pipex pipex);
void	free_sep_path(char **sep_path);
#endif
