/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:36:43 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/26 16:52:42 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(const int *fds, int pipe, char **paths, char **cmdargs)
{
	close(pipe);
	close(fds[1]);
	close(fds[0]);
	desalloc(paths, 0);
	desalloc(cmdargs, 0);
}

int		main(const int ac, char **av, char **env)
{
	int		fds[2];

	if (ac != 5 || !av[2][0] || !av[3][0])
		return (-1);
	if (access(av[4], F_OK) == 0 && access(av[4], W_OK) < 0)
		fds[1] = -2;
	else
		fds[1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(av[1], R_OK) == 0)
		fds[0] = open(av[1], O_RDONLY);
	else
		fds[0] = -2;
	if (fds[0] == -1 || fds[1] == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	pipex(fds, av, env);
	exit(EXIT_FAILURE);
}
