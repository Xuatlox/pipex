/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:32:58 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/26 17:11:51 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void find_cmd(char **paths, char *cmd, char **env, char **cmdargs)
{
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

static void	child1_proc(const int *fds, char *cmd, const int *end, char **env)
{
	char	**cmdargs;
	int		dup[2];
	char	*path_lign;
	char	**paths;

	path_lign = strfind(env, "PATH=");
	paths = ft_split(path_lign, ':');
	if (!paths)
		return (perror("Malloc error"));
	dup[0] = dup2(fds[0], STDIN_FILENO);
	dup[1] = dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fds[0]);
	if (dup[0] < 0|| dup[1] < 0)
		return (perror("dup2 error"));
	cmdargs = ft_split(cmd , ' ');
	if (**cmdargs == '/')
		execve(*cmdargs, cmdargs, env);
	find_cmd(paths, cmd, env, cmdargs);
	free_all(fds, end[1], paths, cmdargs);
	exit(127);
}

static void	child2_proc(const int *fds, char *cmd, const int *end, char **env)
{
	char	**cmdargs;
	int		dup[2];
	char	*path_lign;
	char	**paths;

	path_lign = strfind(env, "PATH=");
	paths = ft_split(path_lign, ':');
	if (!paths)
		return (perror("Malloc error"));
	dup[0] = dup2(end[0], STDIN_FILENO);
	dup[1] = dup2(fds[1], STDOUT_FILENO);
	close(end[1]);
	close(fds[1]);
	if (dup[0] < 0 || dup[1] < 0)
		return (perror("dup2 error"));
	cmdargs = ft_split(cmd, ' ');
	if (**cmdargs == '/')
		execve(*cmdargs, cmdargs, env);
	find_cmd(paths, cmd, env, cmdargs);
	free_all(fds, end[0], paths, cmdargs);
	exit(127);
}

void	pipex(const int *fds, char **av, char **env)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	if (pipe(end) < 0)
		return (perror("Malloc error"));
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork error"));
	if (child1 > 0)
		child2 = fork();
	if (child1 > 0 && child2 < 0)
		return (perror("Fork error"));
	if (child1 == 0 && fds[0] != -2)
		child1_proc(fds, av[2], end, env);
	if (child2 == 0 && fds[1] != -2)
		child2_proc(fds, av[3], end, env);
	waitpid(child1, NULL, 0);
	waitpid(child2, &status, 0);
	close(end[0]);
	close(end[1]);
	close(fds[0]);
	close(fds[1]);
	exit(status >>= 8);
}
