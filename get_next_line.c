/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:48:18 by abenzaho          #+#    #+#             */
/*   Updated: 2024/11/20 18:48:22 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_the_line(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == c)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

char	*get_rest(char *s, char c)
{
	int		i;
	char	*rest;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
		{
			if (s[i + 1] == '\0')
				return (NULL);
			rest = ft_strdup(s + i + 1);
			return (rest);
		}
		i++;
	}
	return (NULL);
}

char	*reading(int fd, char *buffer, char *leftchar)
{
	int		bytes;
	char	*tmp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(leftchar), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(leftchar, buffer);
		if (!tmp)
		{
			free(leftchar);
			return (NULL);
		}
		free(leftchar);
		leftchar = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (leftchar);
}

char	*get_next_line(int fd)
{
	static char	*leftchar;
	char		*str;
	char		*tmp;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	leftchar = reading(fd, buffer, leftchar);
	if (!leftchar)
		return (free(buffer), NULL);
	str = get_the_line(leftchar, '\n');
	tmp = leftchar;
	leftchar = get_rest(leftchar, '\n');
	free(buffer);
	free(tmp);
	return (str);
}
