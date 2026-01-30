/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:24:09 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/30 14:42:40 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

void	proc(const int *input, int *output, char *cmd, char **env);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, char *s3);
void	*ft_calloc(size_t nmemb, size_t size);
void	desalloc(void **res, int i);
void	free_all(const int *fds, int pipe, char **paths, char **cmdargs);
void	close_fds(const int *fds, int **end);
int		pipe_all(int ***end, int nb_pipes);

#endif
