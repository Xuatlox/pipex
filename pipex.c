/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:32:58 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/16 15:39:21 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*strfind(char **tab, const char *prefix)
{
	int		i;

	while (*tab)
	{
		if (**tab == *prefix)
		{
			i = 0;
			while (**tab == prefix[i])
			{
				if (prefix[i + 1] == 0)
					return ((*tab + 1));
				++i;
				++(*tab);
			}
		}
		++tab;
	}
	return (NULL);
}

static void parsing(char **av, char **env)
{
	cmd2args = ft_split(av[3], ' ');
}

static void	child_proc(int fd_in, char *cmd, int *end, char **paths)
{
	if (!dup2(fd_in, STDIN_FILENO)
		|| !dup2(end[1], STDOUT_FILENO))
		exit(EXIT_FAILURE);
	close(end[0]);
	close(fd_in);
}

static void	parent_proc(int fd_out, char *cmd, int *end, char **paths)
{
	char	**cmdargs;

	if (!dup2(end[0], STDIN_FILENO)
		|| !dup2(fd_out, STDOUT_FILENO))
		exit(EXIT_FAILURE);
	close(end[1]);
	close(fd_out);
	cmdargs = ft_split(cmd, ' ');
	while (*paths)
	{
		cmd = ft_strjoin(*paths, *cmdargs);
		execve(cmd, );
		free(cmdargs);
	}
}

void	pipex(const int fd_in, const int fd_out, char **av, char **env)
{
	int   end[2];
	char	*path_lign;
	char	**paths;
	pid_t parent;

	path_lign = strfind(env, "PATH=");
	paths = ft_split(path_lign, ':');
	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork"));
	if (parent == 0)
		child_proc(fd_in, av[2], end, paths);
	else
		parent_proc(fd_out, av[3], end, paths);
	close(end[0]);
	close(end[1]);
}
