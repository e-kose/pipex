/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:37:41 by ekose             #+#    #+#             */
/*   Updated: 2024/01/19 14:34:06 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*cmd_get(char **sep_path, char *cmd_arg)
{
	char	*tmp;
	char	*comand;

	while (*sep_path)
	{
		tmp = ft_strjoin(*sep_path, "/");
		comand = ft_strjoin(tmp, cmd_arg);
		free(tmp);
		if (access(comand, X_OK) == 0)
			return (comand);
		free(comand);
		sep_path++;
	}
	return (NULL);
}
