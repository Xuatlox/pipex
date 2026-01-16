/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:36:43 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/15 13:14:26 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		main(int ac, char **av, char **env)
{
	int		fd_in;
	int		fd_out;

	if (ac != 5)
		return (-1);
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[4], O_WRONLY);
	if (fd_in < 0 || fd_out < 0)
		return (-1);
	pipex(fd_in, fd_out, av, env);
	return (0);
}
