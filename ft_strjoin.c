/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:43:59 by ansimonn          #+#    #+#             */
/*   Updated: 2026/01/19 13:52:12 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2, char *s3)
{
	char	*str;
	char	*res;
	int		size;

	if (!s1 || !s2 || !s3)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	str = malloc(size);
	if (!str)
		return (NULL);
	res = str;
	while (*s1)
		*(str++) = *(s1++);
	while (*s2)
		*(str++) = *(s2++);
	while (*s3)
		*(str++) = *(s3++);
	return (res);
}
