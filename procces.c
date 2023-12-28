/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:29:02 by ekose             #+#    #+#             */
/*   Updated: 2023/12/28 19:48:45 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*comd;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		comd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(comd, X_OK) == 0)
			return (comd);
		free(comd);
		path++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_path, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free(pipex.cmd);
		free(pipex.cmd_args[0]);
		free(pipex.cmd_args[1]);
		free(pipex.cmd_args);
		msg("NOT_cmd_COMMAND");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_path, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free(pipex.cmd);
		free(pipex.cmd_args[0]);
		free(pipex.cmd_args[1]);
		free(pipex.cmd_args);
		msg("NOT_cmd_COMMAND");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
