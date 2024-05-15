/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jretter <jretter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:22 by jretter           #+#    #+#             */
/*   Updated: 2024/05/15 14:12:43 by jretter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Verwendung eines Arrays zur Verwaltung mehrerer Dateideskriptoren

#include "get_next_line_bonus.h"

static char	*ft_get_line(char *speicher)
{
	int		i;
	char	*s;

	i = 0;
	if (!speicher[i])
		return (NULL);
	while (speicher[i] && speicher[i] != '\n')
		i++;
	if (speicher[i] == '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, speicher, i);
	s[i] = '\0';
	return (s);
}

static char	*ft_new_stat(char *speicher)
{
	char	*newline;
	char	*new_str;

	newline = ft_strchr(speicher, '\n');
	if (!newline)
		return (free(speicher), NULL);
	new_str = (char *)malloc(ft_strlen(newline + 1) + 1);
	if (!new_str)
		return (free(speicher), free(new_str), NULL);
	ft_strcpy(new_str, newline + 1);
	return (free(speicher), new_str);
}

static char	*read_str(int fd, char *speicher)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	while (!ft_strchr(speicher, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(speicher), NULL);
		buffer[read_bytes] = '\0';
		speicher = ft_strjoin(speicher, buffer);
		if (!speicher)
			return (NULL);
	}
	return (speicher);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*speicher[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	speicher[fd] = read_str(fd, speicher[fd]);
	if (!speicher[fd])
		return (NULL);
	next_line = ft_get_line(speicher[fd]);
	if (!next_line)
	{
		free(speicher[fd]);
		speicher[fd] = NULL;
	}
	speicher[fd] = ft_new_stat(speicher[fd]);
	return (next_line);
}
