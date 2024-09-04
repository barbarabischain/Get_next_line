/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:19:30 by babischa          #+#    #+#             */
/*   Updated: 2024/05/03 15:03:13 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_rest(char *buffer)
{
	char	*i;
	char	*rest;

	rest = NULL;
	i = ft_strchr(buffer, '\n');
	if (i)
		rest = ft_substr(buffer, (i - buffer + 1), ft_strlen(i + 1));
	else
		rest = ft_strdup("");
	return (rest);
}

static char	*ft_cut(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (0);
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	return (line);
}

static char	*ft_read_fd(int fd, char *read_buffer, char *rest)
{
	int		bytes;
	char	*temp_buffer;
	char	*temp_line;

	temp_buffer = ft_strjoin(rest, "");
	free(rest);
	rest = NULL;
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, read_buffer, BUFFER_SIZE);
		read_buffer[bytes] = '\0';
		temp_line = temp_buffer;
		temp_buffer = ft_strjoin(temp_buffer, read_buffer);
		free(temp_line);
		if (ft_strchr(read_buffer, '\n'))
			return (temp_buffer);
	}
	if (bytes == -1)
	{
		free(rest);
		return (NULL);
	}
	return (temp_buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*full_line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(backup);
		backup = NULL;
		return (0);
	}
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	full_line = ft_read_fd(fd, line, backup);
	free(line);
	line = ft_cut(full_line);
	backup = ft_rest(full_line);
	free(full_line);
	if (*line == '\0' && *backup == '\0')
	{
		free(backup);
		backup = NULL;
		free(line);
		line = NULL;
	}
	return (line);
}
