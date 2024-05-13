/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jretter <jretter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:02 by jretter           #+#    #+#             */
/*   Updated: 2024/05/13 15:12:29 by jretter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *stat)
{
	int		i;
	char	*s;

	i = 0;
	if (!stat[i])
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, stat, i);
	s[i] = '\0';
	return (s);
}

static char	*ft_new_stat(char *stat)
{
	char	*newline;
	char	*new_str;

	newline = ft_strchr(stat, '\n');
	if (!newline)
		return (free(stat), NULL);
	new_str = (char *)malloc(ft_strlen(newline + 1) + 1);
	if (!new_str)
		return (free(stat), free(new_str), NULL);
	ft_strcpy(new_str, newline + 1);
	return (free(stat), new_str);
}

static char	*read_str(int fd, char *stat)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	while (!ft_strchr(stat, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(stat), NULL);
		buffer[read_bytes] = '\0';
		stat = ft_strjoin(stat, buffer);
	}
	return (stat);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stat;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat = read_str(fd, stat);
	if (!stat)
		return (NULL);
	next_line = ft_get_line(stat);
	if (!next_line || next_line[0] == '\0')
	{
		if (stat)
		{
			free(stat);
			stat = NULL;
		}
		return (NULL);
	}
	stat = ft_new_stat(stat);
	return (next_line);
}
int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening file");
		return (1);
	}
	printf("Reading lines alternately from file1 and file2:\n");
	while ((line = get_next_line(fd1)) || (line = get_next_line(fd2)))
	{
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		printf("\n");
		line = get_next_line(fd2);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		printf("\n");
	}
	close(fd1);
	close(fd2);
	return (0);
}
