/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:07:52 by ekose             #+#    #+#             */
/*   Updated: 2023/12/28 19:36:23 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int		pid1;
	int		pid2;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
}			t_pipex;

void	free_pipex(t_pipex *pipex);
void	close_pipex(t_pipex *pipex);
char	*find_path(char **envp, t_pipex *pipex);
void	first_child(t_pipex pipex, char **argv, char **envp);
void	second_child(t_pipex pipex, char **argv, char **envp);
int		msg(char *c);
void	msg_error(char *c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
#endif
