/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:53:28 by ekose             #+#    #+#             */
/*   Updated: 2023/12/28 19:52:12 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
// #include <errno.h>
// #include <stdlib.h>
// #include <string.h>
#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_path[i])
	{
		free(pipex->cmd_path[i]);
		i++;
	}
	free(pipex->cmd_path);
	close(pipex->infile);
	close(pipex->outfile);
}

void	close_pipex(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

char	*find_path(char **envp, t_pipex *pipex)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			check = 1;
		i++;
	}
	if (check == 0)
	{
		msg("ENVP_ERROR");
		close_pipex(pipex);
		close(pipex->infile);
		close(pipex->outfile);
		exit(1);
	}
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp+5);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (msg("number of inputs incorrect\n"));
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		msg_error("infile");
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipex.outfile == -1)
		msg_error("outfile");
	if (pipe(pipex.fd) < 0)
		msg_error("pipe");
	pipex.path = find_path(envp, &pipex);
	pipex.cmd_path = ft_split(pipex.path, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipex(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_pipex(&pipex);
	return (0);
}
