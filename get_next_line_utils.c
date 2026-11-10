/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 13:58:27 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/05 13:58:28 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == (char)c)
		return (s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		len;
	int		i;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	new = malloc((len + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s1[i];
		i++;
	}
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*cut_solved(char *line)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	len = ft_strlen(line);
	if (len - i == 0)
		return (free_line(line, NULL));
	i++;
	new = malloc((len - i + 1) * sizeof(char));
	if (!new)
		return (free_line(line, NULL));
	j = 0;
	while (line[i + j])
	{
		new[j] = line[i + j];
		j++;
	}
	new[j] = '\0';
	free(line);
	return (new);
}
