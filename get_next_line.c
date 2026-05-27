/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrada <fbarrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:39:49 by fbarrada          #+#    #+#             */
/*   Updated: 2026/05/27 14:47:26 by fbarrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_line_break(char *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_line(char *stash)
{
	int		i;
	char	*newstr;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	newstr = malloc(i + 1);
	if (!(newstr))
		return (NULL);
	ft_strncpy(newstr, stash, i);
	newstr[i] = '\0';
	return (newstr);
}

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || stash[i + 1] == '\0')
		return (free(stash), NULL);
	i++;
	while (stash[i] && stash[j + i])
		j++;
	newstr = malloc(j + 1);
	if (!(newstr))
		return (free(stash), NULL);
	ft_strncpy(newstr, stash + i, j);
	newstr[j] = '\0';
	return (free(stash), newstr);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	stash = read_file(fd, stash);
	if (!stash || !*stash)
		return (free(stash), NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	if (!stash || !*stash)
		stash = NULL;
	return (line);
}
