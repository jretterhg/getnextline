/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jretter <jretter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:15 by jretter           #+#    #+#             */
/*   Updated: 2024/05/15 12:17:35 by jretter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *string, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*jstr;

	if (!string)
	{
		string = (char *)malloc(1 * sizeof(char));
		if (!string)
			return (NULL);
		string[0] = '\0';
	}
	if (!string || !buffer)
		return (NULL);
	jstr = malloc(sizeof(char) * ((ft_strlen(string) + ft_strlen(buffer)) + 1));
	if (!jstr)
		return (free(string), NULL);
	i = -1;
	j = 0;
	if (string)
		while (string[++i] != '\0')
			jstr[i] = string[i];
	while (buffer[j] != '\0')
		jstr[i++] = buffer[j++];
	jstr[ft_strlen(string) + ft_strlen(buffer)] = '\0';
	return (free(string), jstr);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	length;

	length = 0;
	while (src[length] != '\0')
	{
		dest[length] = src[length];
		length++;
	}
	dest[length] = '\0';
	return (dest);
}
