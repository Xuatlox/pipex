/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:32:58 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/29 17:36:38 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

void	proc(const int *input, const int *output, char *cmd, char **env);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, char *s3);
void	*ft_calloc(size_t nmemb, size_t size);
void	desalloc(void **res, int i);
void	free_all(const int *fds, int pipe, char **paths, char **cmdargs);
void	close_fds(const int *input, const int *output);
int		pipe_all(int ***end, int nb_pipes);
int		fork_all(pid_t *pid, int cmd_n);

#endif
