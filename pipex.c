/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:32:58 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/19 18:38:15 by ansimonn         ###   ########.fr       */
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

static void	child_proc(const int fd_in, char *cmd, const int *end, char **paths, char **env)
{
	char **cmdargs;
	int		dup[2];

	dup[0] = dup2(fd_in, STDIN_FILENO);
	dup[1] = dup2(end[1], STDOUT_FILENO);
	if (dup[0] < 0|| dup[1] < 0)
		return (perror("dup2 error"));
	close(end[1]);
	cmdargs = ft_split(cmd , ' ');
	while (*paths)
	{
		cmd = ft_strjoin(*paths, "/", *cmdargs);
		execve(cmd, cmdargs, env);
		++paths;
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

static void	parent_proc(const int fd_out, char *cmd, const int *end, char **paths, char **env)
{
	char	**cmdargs;
	int		status;
	int		dup[2];

	wait(&status);
	dup[0] = dup2(end[0], STDIN_FILENO);
	dup[1] = dup2(fd_out, STDOUT_FILENO);
	if (dup[0] < 0 || dup[1] < 0)
		return (perror("dup2 error"));
	close(end[1]);
	cmdargs = ft_split(cmd, ' ');
	while (*paths)
	{
		cmd = ft_strjoin(*paths, "/", *cmdargs);
		execve(cmd, cmdargs, env);
		free(cmd);
		++paths;
	}
	exit(EXIT_FAILURE);
}

void	pipex(const int fd_in, const int fd_out, char **av, char **env)
{
	int   end[2];
	char	*path_lign;
	char	**paths;
	pid_t parent;

	path_lign = strfind(env, "PATH=");
	paths = ft_split(path_lign, ':');
	if (pipe(end) < 0)
		return(perror("Pipe error"));
	parent = fork();
	if (parent < 0)
		return (perror("Fork error"));
	if (parent == 0)
		child_proc(fd_in, av[2], end, paths, env);
	close(end[1]);
	if (parent > 0)
		parent_proc(fd_out, av[3], end, paths, env);
	close(end[0]);
	close(fd_in);
	close(fd_out);
}
