/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:39:18 by babischa          #+#    #+#             */
/*   Updated: 2024/01/19 13:43:46 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*mem;
	size_t	i;

	total = count * size;
	mem = malloc(total);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < total)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}

/*STRDUP*/
char	*ft_strdup(char *s)
{
	char	*line;
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	line = ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (0);
	return (line);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	lens1;
	size_t	lens2;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	new = ft_calloc((lens1 + lens2 + 1), sizeof(char));
	if ((!s1 && !s2) || !new)
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < (lens1 + lens2))
	{
		new[i] = s2[j++];
		i++;
	}
	return (new);
}

/*STRCHR*/
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	if ((unsigned char)c == '\0')
		return (ptr);
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	lenstr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	lenstr = ft_strlen(s);
	if (lenstr - start < len)
		len = lenstr - start;
	if (start >= lenstr)
		return (ft_strdup(""));
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (0);
	while (i < len && start < lenstr)
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
