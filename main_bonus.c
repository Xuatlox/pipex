/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:56:03 by ansimonn          #+#    #+#             */
/*   Updated: 2026/02/02 16:52:24 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds(const int *fds, int **end)
{
	int i;

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

static pid_t *fork_all(const int *fds, char **cmds, int **end, char **env)
{
	int	i;
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
			close_unused(fds, end, i);
			if (i == 0)
				proc(fds, end[0], cmds[0], env);
			else
				proc(end[i - 1], end[i], cmds[i], env);
			close_fds(fds, end);
			exit(1);
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
		close_unused(fds, end, cmd_n - 1);
		proc(end[cmd_n - 2], fds, cmds[cmd_n - 1], env);
		close_fds(fds, end);
		exit(1);
	}
	close_fds(fds, end);
	desalloc((void **) end, 0);
	status = wait_all(pids);
	exit(status);
}

static void	check_args(char **av)
{
	while (*(av + 1))
	{
		if (**av == 0)
			exit(EXIT_FAILURE);
		++av;
	}
}

int	main(const int ac, char **av, char **env)
{
	int		fds[2];

	if (ac < 5)
		return (0);
	check_args(av + 2);
	if (access(av[1], R_OK) == 0)
		fds[0] = open(av[1], O_RDONLY);
	else
		fds[0] = -2;
	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK | R_OK) < 0)
		fds[1] = -2;
	else
		fds[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds[0] == -1 || fds[1] == -1)
	{
		if (fds[1] == -1)
			close(fds[0]);
		if (fds[0] == -1)
			close(fds[1]);
		return (-1);	}
	pipeline(fds, ac - 3, av + 2, env);
	close_fds(fds, NULL);
	return (0);
}
