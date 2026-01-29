/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:23:12 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/29 17:41:52 by ansimonn         ###   ########.fr       */
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
		**end = malloc(sizeof(int) * 3);
		**end[2] = 0;
		if (pipe(**end) < 0)
		{
			desalloc((void **) *end, 0);
			return (0);
		}
		++i;
	}
	return (1);
}

pid_t	fork_all(pid_t *pid, const int pid_n)
{
	pid_t	*p;

	if (!*pid)
		return (0);
	while (**pid != 1)
	{
		*pid = fork();
		if (*pid < 0)
			return (0);
		if (**pid == 0)
			return (1);
		++*pid;
	}
	return (1);
}
