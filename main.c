/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:36:43 by ansimonn          #+#    #+#             */
/*   Updated: 2026/02/04 17:15:07 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	error(const char *msg, const int *fds, const int *end)
{
	perror(msg);
	close_fds(fds, end);
	exit(EXIT_FAILURE);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;

	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}

void	close_fds(const int *input, const int *output)
{
	if (input[0] >= 0)
		close(input[0]);
	if (input[1] >= 0)
		close(input[1]);
	if (output[0] >= 0)
		close(output[0]);
	if (output[1] >= 0)
		close(output[1]);
}

void	pipeline(const int *fds, char **av, char **env, int *status)
{
	int		end[2];
	pid_t	pid[2];
	int		i;

	if (pipe(end) < 0)
		error("Pipe error", fds, end);
	i = -1;
	while (++i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			error("Fork error", fds, end);
		if (i == 0 && pid[i] == 0 && fds[0] >= 0)
			proc(fds, end, av[2], env);
		if (i == 1 && pid[i] == 0 && fds[1] >= 0)
			proc(end, fds, av[3], env);
		if (pid[i] == 0)
		{
			close_fds(fds, end);
			exit(EXIT_FAILURE);
		}
	}
	close_fds(fds, end);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], status, 0);
}

int	main(const int ac, char **av, char **env)
{
	int		fds[2];
	int		status;

	if (ac != 5 || !av[2][0] || !av[3][0])
		return (0);
	if (access(av[1], R_OK) == 0)
		fds[0] = open(av[1], O_RDONLY);
	else
		fds[0] = -2;
	if (access(av[4], F_OK) == 0 && access(av[4], W_OK | R_OK) < 0)
		fds[1] = -2;
	else
		fds[1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds[0] == -1 || fds[1] == -1)
	{
		if (fds[1] == -1)
			close(fds[0]);
		if (fds[0] == -1)
			close(fds[1]);
		return (-1);
	}
	pipeline(fds, av, env, &status);
	exit(status >> 8);
}
