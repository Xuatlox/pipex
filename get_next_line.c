/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:24:57 by ansimonn          #+#    #+#             */
/*   Updated: 2026/02/03 14:14:33 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*search_sep(char **buf, int *size, int fd)
{
	int		ret;

	if (!*buf)
		return ("");
	ret = read(fd, &(*buf)[*size], BUFFER_SIZE);
	if (ret == -1)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	if (ret == 0)
		return (&(*buf)[*size]);
	return (find_newline(buf, size));
}

static int	check_null(char **buf, char **sep)
{
	if (!*buf || !**buf)
	{
		free(*buf);
		*sep = NULL;
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*sep;
	int			size;

	if (fd < 0 || fd > 1024)
		return (NULL);
	buf = sep;
	size = 0;
	if (buf)
		sep = find_newline(&buf, &size);
	else
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!sep)
		sep = search_sep(&buf, &size, fd);
	if (check_null(&buf, &sep))
		return (NULL);
	if (*sep && *(sep + 1))
		sep = ft_strdup(sep + 1);
	else
		sep = NULL;
	buf[size + 1] = 0;
	return (buf);
}
