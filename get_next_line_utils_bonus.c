/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 17:19:13 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/08 17:19:15 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == c)
		return (str);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*new;
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

char	*cut_line(char *line)
{
	char	*cut;
	int		j;
	int		i;
	int		len;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	len = ft_strlen(line);
	if (len - i == 0)
		return (free(line), NULL);
	i++;
	cut = malloc((len - i + 1) * sizeof(char));
	if (!cut)
		return (free(line), NULL);
	j = 0;
	while (line[i + j])
	{
		cut[j] = line[i + j];
		j++;
	}
	cut[j] = '\0';
	free(line);
	return (cut);
}
