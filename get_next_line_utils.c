/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:36:58 by ansimonn          #+#    #+#             */
/*   Updated: 2025/11/24 10:58:05 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*resize(char *s, const int *size)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(*size + BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i < *size)
	{
		str[i] = s[i];
		i++;
	}
	free(s);
	return (str);
}

char	*find_newline(char **s, int *size)
{
	if (!*s)
		return (NULL);
	while ((*s)[*size])
	{
		if ((*s)[*size] == '\n')
			return (*s + *size);
		(*size)++;
	}
	*s = resize(*s, size);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i])
		i++;
	dup = ft_calloc((i + 1), sizeof(char));
	if (!dup)
		return (NULL);
	i--;
	while (i >= 0)
	{
		dup[i] = s[i];
		i--;
	}
	return (dup);
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
