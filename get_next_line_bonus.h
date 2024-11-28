/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:56:15 by abenzaho          #+#    #+#             */
/*   Updated: 2024/11/28 16:56:27 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# define BUFFER_SIZE 42

size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s);
void	ft_copy(const char *src, char *dst);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, char c);
char	*get_next_line(int fd);
char	*reading(int fd, char **leftchar);
char	*get_rest(char *s, char c);
char	*get_line(char *s, char c);

#endif
