/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:55:33 by abenzaho          #+#    #+#             */
/*   Updated: 2024/11/28 16:55:37 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*reading(int fd, char *leftchar)
{
	int		bytes;
	char	*tmp;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(leftchar, buffer);
		if (!tmp)
			return (free(buffer), free(leftchar), NULL);
		free(leftchar);
		leftchar = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), leftchar);
}

char	*get_next_line(int fd)
{
	static char	*leftchar[1024];
	char		*str;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	leftchar[fd] = reading(fd, leftchar[fd]);
	if (!leftchar[fd])
		return (NULL);
	str = get_the_line(leftchar[fd], '\n');
	tmp = leftchar[fd];
	leftchar[fd] = get_rest(leftchar[fd], '\n');
	return (free(tmp), str);
}
