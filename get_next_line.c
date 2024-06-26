/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jretter <jretter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:02 by jretter           #+#    #+#             */
/*   Updated: 2024/05/15 14:21:43 by jretter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *speicher)
{
	int		i;
	char	*sneu;

	i = 0;
	if (!speicher[i])
		return (NULL);
	while (speicher[i] && speicher[i] != '\n')
		i++;
	if (speicher[i] == '\n')
		i++;
	sneu = (char *)malloc(sizeof(char) * (i + 1));
	if (!sneu)
		return (NULL);
	ft_memcpy(sneu, speicher, i);
	sneu[i] = '\0';
	return (sneu);
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
	}
	return (speicher);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*speicher;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	speicher = read_str(fd, speicher);
	if (!speicher)
		return (NULL);
	next_line = ft_get_line(speicher);
	if (!next_line || next_line[0] == '\0')
	{
		if (speicher)
		{
			free(speicher);
			speicher = NULL;
		}
		return (NULL);
	}
	speicher = ft_new_stat(speicher);
	return (next_line);
}

// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	char	*line;

// 	fd1 = open("file1.txt", O_RDONLY);
// 	fd2 = open("file2.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	printf("Reading lines from file1 and file2:\n\n");
// 	while ((line = get_next_line(fd1)) || (line = get_next_line(fd2)))
// 	{
// 		if (line)
// 		{
// 			printf("%s", line);
// 			free(line);
// 		}
// 		printf("\n");
// 		line = get_next_line(fd2);
// 		if (line)
// 		{
// 			printf("%s", line);
// 			free(line);
// 		}
// 		printf("\n");
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }
//
