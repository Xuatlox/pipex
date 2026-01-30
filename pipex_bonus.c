/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:39:35 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/30 16:57:35 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exec_cmd(char **paths, char *cmd, char **env, char **cmdargs)
{
	int		i;

	i = 0;
	if (**cmdargs == '/' && access(*cmdargs, X_OK) == 0)
		execve(*cmdargs, cmdargs, env);
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/", *cmdargs);
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) < 0)
			perror("can't execute command");
		else if (access(cmd, X_OK) == 0)
		{
			desalloc((void **) paths, 0);
			execve(cmd, cmdargs, env);
		}
		free(cmd);
		++i;
	}
	desalloc((void **) paths, 0);
	desalloc((void **) cmdargs, 0);
}

static char	*strfind(char **tab, const char *prefix)
{
	int		i;
	int		j;

	while (*tab)
	{
		if (**tab == *prefix)
		{
			i = 0;
			j = 0;
			while ((*tab)[j] == prefix[i])
			{
				if (prefix[i + 1] == 0)
					return ((*tab + j + 1));
				++i;
				++j;
			}
		}
		++tab;
	}
	return (NULL);
}

void	proc(const int *input, int *output, char *cmd, char **env)
{
	char	**cmdargs;
	int		dup[2];
	char	*path_lign;
	char	**paths;

	path_lign = strfind(env, "PATH=");
	if (!path_lign)
		write(2, "ERROR\n", 6);
	paths = ft_split(path_lign, ':');
	if (!paths)
		exit(127);
	dup[0] = dup2(input[0], STDIN_FILENO);
	dup[1] = dup2(output[1], STDOUT_FILENO);
	close_fds(input, NULL);
	close_fds(output, NULL);
	if (dup[0] < 0 || dup[1] < 0)
	{
		desalloc((void **) paths, 0);
		exit(127);
	}
	cmdargs = ft_split(cmd, ' ');
	exec_cmd(paths, cmd, env, cmdargs);
	exit(127);
}
