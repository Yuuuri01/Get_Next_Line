/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 14:42:44 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/05 14:43:15 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_line(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*read_one(int fd, char *line)
{
	char	buff[CHUNK + 1];
	int		bytes;
	char	c;
	int		i;

	if (line && ft_strchr(line, '\n'))
		return (line);
	i = 0;
	c = 0;
	bytes = 1;
	while (bytes && c != '\n')
	{
		bytes = read(fd, &c, 1);
		if (bytes == -1)
			return (free_line(line, NULL));
		if (bytes == 1)
			buff[i++] = c;
		if (i == CHUNK || bytes == 0 || c == '\n')
		{
			buff[i] = '\0';
			line = ft_strjoin(line, buff);
			i = 0;
		}
	}
	return (line);
}

char	*solve_line(char *line)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i += 1;
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	len = i;
	i = 0;
	while (line[i] && i < len)
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*read_line(char *line, int fd)
{
	char	*buff;
	int		bytes;

	if (line && ft_strchr(line, '\n'))
		return (line);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free_line(buff, line));
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			return (free_line(buff, NULL));
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (BUFFER_SIZE == 1)
		line = read_one(fd, line);
	else
		line = read_line(line, fd);
	if (!line || !*line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	result = solve_line(line);
	if (!result)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = cut_solved(line);
	return (result);
}
