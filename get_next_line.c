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

char	*get_line(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && (i && s[i - 1] != c))
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && (i && s[i - 1] != c))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_rest(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != '\n')
			return (ft_strdup(s + i + 1));
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			bytes;
	char		*buffer;
	static char	*leftchar;
	char		*str;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	while (1)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (!leftchar)
		{
			str = ft_strjoin(str, get_line(buffer, '\n'));
			leftchar = ft_strjoin(leftchar, get_rest(buffer, '\n'));
		}
		else
		{
			str = ft_strjoin(str, get_line(leftchar, '\n'));
			leftchar = get_rest(leftchar, '\n');
			leftchar = ft_strjoin(leftchar, buffer);
		}
		if (ft_strchr(buffer, '\n') || !leftchar)
			break ;
		free(buffer);
	}
	free (buffer);
	return (str);
}

#include <stdio.h>

char *get_next_line(int fd); 

int main(void)
{
    int fd;

    fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
        printf("%s", get_next_line(fd));
    return (0);
}
