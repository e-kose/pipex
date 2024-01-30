/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:58:43 by ekose             #+#    #+#             */
/*   Updated: 2024/01/20 12:05:40 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_procces(t_pipex pipex, char **argv, char **envp)
{
	char	**cmd_arg;
	char	*cmd_path;

	cmd_arg = ft_split(argv[2], ' ');
	dup2(pipex.fd[1], STDOUT_FILENO);
	close(pipex.fd[0]);
	dup2(pipex.infile, STDIN_FILENO);
	cmd_path = cmd_get(pipex.sep_path, cmd_arg[0]);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		free(cmd_arg[0]);
		free(cmd_arg[1]);
		free(cmd_arg);
		err_msg("Command not found ");
	}
	if ((execve(cmd_path, cmd_arg, envp) == -1))
		msg("Execve");
}

void	second_child_procces(t_pipex pipex, char **argv, char **envp)
{
	char	**cmd_arg;
	char	*cmd_path;

	cmd_arg = ft_split(argv[3], ' ');
	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	cmd_path = cmd_get(pipex.sep_path, cmd_arg[0]);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		free(cmd_arg[0]);
		free(cmd_arg[1]);
		free(cmd_arg);
		err_msg("Command not found");
	}
	if ((execve(cmd_path, cmd_arg, envp) == -1))
		msg("Execve");
}
