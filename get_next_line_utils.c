/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrada <fbarrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:40:26 by fbarrada          #+#    #+#             */
/*   Updated: 2026/05/27 14:09:26 by fbarrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *stash)
{
	size_t	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	size_s1;
	size_t	size_s2;
	size_t	totalsize;
	char	*newstr;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	i = 0;
	j = 0;
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	totalsize = size_s1 + size_s2;
	newstr = malloc(totalsize + 1);
	if (!newstr)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
		newstr[i++] = s2[j++];
	newstr[totalsize] = '\0';
	return (free(s1), newstr);
}
