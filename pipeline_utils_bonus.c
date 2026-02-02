/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:23:12 by ansimonn          #+#    #+#             */
/*   Updated: 2026/02/02 15:39:31 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pipe_all(int ***end, const int nb_pipes)
{
	int	i;

	i = 0;
	*end = calloc((nb_pipes + 1), sizeof(int *));
	if (!*end)
		return (0);
	while (i < nb_pipes)
	{
		(*end)[i] = malloc(sizeof(int) * 3);
		(*end)[i][2] = 0;
		if (pipe((*end)[i]) < 0)
		{
			desalloc((void **) *end, 0);
			return (0);
		}
		++i;
	}
	return (1);
}

static void close_last_fds(int **end)
{
	int	i;

	i = 0;
	while (end[i + 1])
	{
		if (end[i][0] >= 0)
			close(end[i][0]);
		if (end[i][1] >= 0)
			close(end[i][1]);
		++i;
	}
}

void close_unused(const int *fds, int **end, const int i)
{
	int	j;

	if (i == 0)
	{
		close_fds(NULL, &end[1]);
		return ;
	}
	if (ft_arsize((void **) end) == i)
	{
		close_last_fds(end);
		return ;
	}
	j = 0;
	close(fds[0]);
	close(fds[1]);
	while (end[j])
	{
		if (j != i && j != i - 1)
		{
			close(end[j][0]);
			close(end[j][1]);
		}
		++j;
	}
}

int		wait_all(pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &status, 0);
		++i;
	}
	free(pids);
	return (status >> 8);
}

int		ft_arsize(void **ar)
{
	int	i;

	i = 0;
	if (!ar)
		return (0);
	while (ar[i])
		++i;
	return (i);
}
