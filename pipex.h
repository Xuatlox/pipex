/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:32:58 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/26 16:06:59 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void	pipex(int const *fds, char **av, char **env);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, char *s3);
void	*ft_calloc(size_t nmemb, size_t size);
char	**desalloc(char **res, int i);
void	free_all(const int *fds, int pipe, char **paths, char **cmdargs);

#endif
