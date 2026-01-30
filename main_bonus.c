/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:56:03 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/30 17:12:16 by ansimonn         ###   ########.fr       */
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

static void fork_all(const int *fds, char **cmds, int **end, char **env)
{
	int	i;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Fork error"));
	if (pid == 0)
	{
		proc(fds, end[0], cmds[0], env);
		close_fds(fds, end);
		exit(1);
	}
	i = 0;
	while (cmds[++i + 2])
	{
		pid = fork();
		if (pid < 0)
			return (perror("Fork error"));
		if (pid == 0)
		{
			proc(end[i - 1], end[i], cmds[i], env);
			close_fds(fds, end);
			exit(1);
		}
	}
}

void	pipeline(int *fds, int cmd_n, char **cmds, char **env)
{
	int		**end;
	pid_t	pid_last;
	int		status;

	if (!pipe_all(&end, cmd_n - 1))
		return ;
	pid_last = fork();
	if (pid_last < 0)
	{
		close_fds(fds, end);
		return (perror("Fork error"));
	}
	if (pid_last == 0)
	{
		proc(end[cmd_n - 2], fds, cmds[cmd_n - 1], env);
		close_fds(fds, end);
		exit(1);
	}
	fork_all(fds, cmds, end, env);
	close_fds(fds, end);
	while (--cmd_n)
		wait(NULL);
	waitpid(pid_last, &status, 0);
	exit(status >> 8);
}

static void	check_cmds(char **av)
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
	check_cmds(av + 2);
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
		return (-1);
	}
	pipeline(fds, ac - 3, av + 2, env);
	close_fds(fds, NULL);
	return (0);
}
