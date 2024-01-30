/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:35:18 by ekose             #+#    #+#             */
/*   Updated: 2024/01/20 11:50:08 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	int	check;

	check = 0;
	while (*envp)
	{
		if ((ft_strncmp(*envp, "PATH", 4) == 0))
		{
			check = 1;
			break ;
		}
		envp++;
	}
	if (check == 0)
		return (NULL);
	return (*envp + 5);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc == 5)
		transactions(&pipex, argc, argv);
	else
		err_msg("number of invalid arguments!!");
	pipex.path = find_path(envp);
	if (pipex.path == NULL)
		err_msg("ENVP_ERROR!!");
	pipex.sep_path = ft_split(pipex.path, ':');
	if (pipe(pipex.fd) == -1)
		err_msg("Pipe");
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child_procces(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child_procces(pipex, argv, envp);
	ft_close(pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_sep_path(pipex.sep_path);
}
