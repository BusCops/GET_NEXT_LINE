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
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
		{
			if (s[i + 1] == '\0')
				return (NULL);
			return (ft_strdup(s + i + 1));
		}
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		leftchar = ft_strjoin(leftchar, buffer);
		if (ft_strchr(leftchar, '\n') || !leftchar)
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes < 0 || (!leftchar && bytes == 0))
		return (NULL);
	str = get_line(leftchar, '\n');
	leftchar = get_rest(leftchar, '\n');
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
    printf("line->%s", get_next_line(fd));
    printf("line->%s", get_next_line(fd));
    printf("line->%s", get_next_line(fd));
    printf("line->%s", get_next_line(fd));
    printf("line->%s", get_next_line(fd));
    printf("line->%s", get_next_line(fd));
    printf("line->%s", get_next_line(fd));
    printf("line->%s", get_next_line(fd));


	return (0);
}
