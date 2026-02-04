/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:56:03 by ansimonn          #+#    #+#             */
/*   Updated: 2026/02/04 16:23:12 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds(const int *fds, int **end)
{
	int	i;

	if (fds)
	{
		if (fds[0] >= 0)
			close(fds[0]);
		if (fds[1] >= 0)
			close(fds[1]);
	}
	if (end)
	{
		i = 0;
		while (end[i])
		{
			if (end[i][0] >= 0)
				close(end[i][0]);
			if (end[i][1] >= 0)
				close(end[i][1]);
			++i;
		}
	}
}

static pid_t	*fork_all(const int *fds, char **cmds, int **end, char **env)
{
	int		i;
	pid_t	*pids;

	i = -1;
	pids = ft_calloc(ft_arsize((void **) cmds), sizeof(pid_t));
	while (cmds[++i + 2])
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("Fork error");
			return (NULL);
		}
		if (pids[i] == 0)
		{
			close_unused(fds, end, i, pids);
			if (i == 0)
				proc(fds, end[0], cmds[0], env);
			else
				proc(end[i - 1], end[i], cmds[i], env);
			free_close(end, i, fds);
			exit(127);
		}
	}
	return (pids);
}

void	pipeline(int *fds, int cmd_n, char **cmds, char **env)
{
	int		**end;
	pid_t	*pids;
	int		status;

	if (!pipe_all(&end, cmd_n - 1))
		return ;
	pids = fork_all(fds, cmds, end, env);
	pids[cmd_n - 1] = fork();
	if (pids[cmd_n - 1] < 0)
	{
		close_fds(fds, end);
		return (perror("Fork error"));
	}
	if (pids[cmd_n - 1] == 0)
	{
		close_unused(fds, end, cmd_n - 1, pids);
		status = proc(end[cmd_n - 2], fds, cmds[cmd_n - 1], env);
		free_close(end, cmd_n - 1, fds);
		exit(status);
	}
	close_fds(fds, end);
	desalloc((void **) end, 0);
	status = wait_all(pids);
	exit(status);
}

static void	check_args(char ***av, int *ac, int *fds)
{
	int	i;

	if (ft_strcmp((*av)[1], "here_doc") == 0)
	{
		fds[0] = -3;
		++(*av);
		--(*ac);
	}
	else
		fds[0] = 0;
	i = 0;
	while ((*av)[i])
	{
		if ((*av)[i][0] == 0)
			exit(EXIT_FAILURE);
		++i;
	}
}

int	main(int ac, char **av, char **env)
{
	int		fds[2];

	if (ac < 5)
		return (0);
	check_args(&av, &ac, fds);
	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK | R_OK) < 0)
		fds[1] = -2;
	else if (fds[0] == -3)
		fds[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fds[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds[0] == -3)
		here_doc(fds, av);
	else if (access(av[1], R_OK) == 0)
		fds[0] = open(av[1], O_RDONLY);
	else
		fds[0] = -2;
	if (fds[0] == -1 || fds[1] == -1)
	{
		close_fds(fds, NULL);
		return (-1);
	}
	pipeline(fds, ac - 3, av + 2, env);
	close_fds(fds, NULL);
	return (0);
}
