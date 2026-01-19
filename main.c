/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:36:43 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/19 15:17:42 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		main(const int ac, char **av, char **env)
{
	int		fd_in;
	int		fd_out;

	if (ac != 5)
		return (-1);
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_in < 0 || fd_out < 0)
		return (-1);
	pipex(fd_in, fd_out, av, env);
	return (0);
}
