/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:36:43 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/29 17:41:52 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds(const int *input, const int *output)
{
	if (input)
	{
		if (input[0] >= 0)
			close(input[0]);
		if (input[1] >= 0)
			close(input[1]);
	}
	if (output)
	{
		if (output[0] >= 0)
			close(output[0]);
		if (output[1] >= 0)
			close(output[1]);
	}
}

void	pipeline(const int *fds, int cmd_n, char **av, char **env)
{
	int		**end;
	pid_t	pid;
	int		status;

	if (!pipe_all(&end, cmd_n - 1) || !fork_all(&pid, cmd_n))
		return ;
	if (*pid == 0)
		proc(end);
	/*while (*(av + 1))
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (perror("Fork error"));
		if (i == 0 && pid[i] == 0 && fds[0] >= 0)
			proc(fds, end, av[2], env);
		if (i == 1 && pid[i] == 0 && fds[1] >= 0)
			proc(end, fds, av[3], env);
		if (pid[i] == 0)
		{
			close_fds(fds, end);
			exit(1);
		}
		++av;
	}*/
	close_fds(fds, end);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	exit(status >> 8);
}

static void	check_cmds(char **av)
{
	while (av + 1)
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
