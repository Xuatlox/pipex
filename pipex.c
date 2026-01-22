/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:32:58 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/22 16:24:53 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void free_all(int const *fds_free, const int pipe_free, char **paths, char **cmdargs)
{
	close(pipe_free);
	close(fds_free[1]);
	close(fds_free[0]);
	desalloc(paths, 0);
	desalloc(cmdargs, 0);
}

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

static void	child_proc(int const *fds, char *cmd, const int *end, char **paths, char **env)
{
	char **cmdargs;
	int		dup[2];
	char	**paths_adr;

	dup[0] = dup2(fds[0], STDIN_FILENO);
	dup[1] = dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fds[0]);
	if (dup[0] < 0|| dup[1] < 0)
		return (perror("dup2 error"));
	cmdargs = ft_split(cmd , ' ');
	if (**cmdargs == '/')
		execve(*cmdargs, cmdargs, env);
	paths_adr = paths;
	while (*paths)
	{
		cmd = ft_strjoin(*paths, "/", *cmdargs);
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) < 0)
			perror("can't execute command");
		else if (access(cmd, X_OK) == 0)
			execve(cmd, cmdargs, env);
		++paths;
		free(cmd);
	}
	free_all(fds, end[1], paths_adr, cmdargs);
	exit(127);
}

static void	parent_proc(int const *fds, char *cmd, const int *end, char **paths, char **env)
{
	char	**cmdargs;
	int		dup[2];
	char	**paths_adr;

	dup[0] = dup2(end[0], STDIN_FILENO);
	dup[1] = dup2(fds[1], STDOUT_FILENO);
	close(end[1]);
	close(fds[1]);
	if (dup[0] < 0 || dup[1] < 0)
		return (perror("dup2 error"));
	cmdargs = ft_split(cmd, ' ');
	if (**cmdargs == '/')
		execve(*cmdargs, cmdargs, env);
	paths_adr = paths;
	while (*paths)
	{
		cmd = ft_strjoin(*paths, "/", *cmdargs);
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) < 0)
			perror("can't execute command");
		else if (access(cmd, X_OK) == 0)
			execve(cmd, cmdargs, env);
		free(cmd);
		++paths;
	}
	free_all(fds, end[0], paths_adr, cmdargs);
	exit(127);
}

void	pipex(int const *fds, char **av, char **env)
{
	int		end[2];
	char	*path_lign;
	char	**paths;
	pid_t	parent;
	int		status;

	path_lign = strfind(env, "PATH=");
	paths = ft_split(path_lign, ':');
	if (!paths || pipe(end) < 0)
		return (perror("Malloc error"));
	parent = fork();
	if (parent < 0)
		return (perror("Fork error"));
	if (parent == 0 && fds[0] != -2)
		child_proc(fds, av[2], end, paths, env);
	if (parent > 0)
		wait(&status);
	if (parent > 0 && fds[1] != -2)
		parent_proc(fds, av[3], end, paths, env);
	close(end[0]);
	close(end[1]);
	desalloc(paths, 0);
}
