/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrada <fbarrada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:41:11 by fbarrada          #+#    #+#             */
/*   Updated: 2026/05/27 14:05:40 by fbarrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5

# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *stash);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strjoin(char *s1, char *s2);
int		check_line_break(char *stash);
char	*extract_line(char *stash);
char	*clean_stash(char *stash);
char	*get_next_line(int fd);

#endif