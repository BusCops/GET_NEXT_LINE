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

char	*get_line(char *s, char c)
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
			free(s);
			return (rest);
		}
		i++;
	}
	return (NULL);
}

char	**reading(int fd, char **leftchar)
{
	int		bytes;
	char	*tmp;
	char	buffer[BUFFER_SIZE +1];

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(leftchar[fd], buffer);
		if (!tmp)
		{
			free(leftchar[fd]);
			return (NULL);
		}
		free(leftchar[fd]);
		leftchar[fd] = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (leftchar[fd]);
}

char	*get_next_line(int fd)
{
	static char	**leftchar;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    if (!leftchar)
    {
        leftcahr = (char **)malloc(1024 * sizeof(char *));
        if (!leftchar)
            return (NULL);
    }
	leftchar[fd] = reading(fd, leftchar[fd]);
	if (!leftchar[fd])
		return (NULL);
	str = get_line(leftchar[fd], '\n');
	leftchar[fd] = get_rest(leftchar[fd], '\n');
	return (str);
}
