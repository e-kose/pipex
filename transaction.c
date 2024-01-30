/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:33:52 by ekose             #+#    #+#             */
/*   Updated: 2024/01/19 18:37:12 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	transactions(t_pipex *pipex, int argc, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		msg(argv[1]);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (pipex->outfile == -1)
		msg(argv[argc - 1]);
}

void	free_sep_path(char **sep_path)
{
	int	i;

	i = 0;
	while (sep_path[i])
	{
		free(sep_path[i]);
		i++;
	}
	free(sep_path);
}

void	ft_close(t_pipex pipex)
{
	close(pipex.infile);
	close(pipex.infile);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
}
